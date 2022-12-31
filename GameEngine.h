#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <SFML/OpenGL.hpp>
#include "KeyboardIn.h"
#include "KeyboardOut.h"
#include "Render.h"
#include "Controls.h"
#include "GameObject.cpp"
#include <thread>
#include <deque>
#include <future>


class Scene;

class Pool {
public:

	std::mutex m;
	std::condition_variable v;

	std::deque<std::packaged_task<void()>> jobs;

	std::vector<std::future<void>> finished;


	template<class F, class R = std::result_of_t<F& ()>>
	std::future<R> queue(F&& f) {
		std::packaged_task<R()> p(std::forward<F>(f));


		auto r = p.get_future();
		{
			std::unique_lock<std::mutex> l(m);
			jobs.emplace_back(std::move(p));
		}
		v.notify_one();

		return r;
	}


	void start(int n) {
		for (int i = 0; i < n; i++) {
			finished.push_back(std::async(std::launch::async, [this] {task(); }));
		}
	}

	void abort() {
		cancelPending();
		finish();
	}

	void cancelPending() {
		std::unique_lock<std::mutex> l(m);
		jobs.clear();
	}


	void finish() {
		std::unique_lock<std::mutex> l(m);
		for (auto&& unused : finished) {
			jobs.push_back({});
		}
		v.notify_all();
		finished.clear();
	}
	~Pool() {
		finish();
	}


private:

	void task() {
		while (true) {
			std::packaged_task<void()> f;
			{
				std::unique_lock<std::mutex> l(m);

				if (jobs.empty()) {
					v.wait(l, [&] {return !jobs.empty(); });

				}
				f = std::move(jobs.front());
				jobs.pop_front();
			}
			if (!f.valid())return;

			f();
		}

	}



};


class GameEngine {
public:

	shared_ptr<KeyboardIn> keyboardIn = shared_ptr<KeyboardIn>(new KeyboardIn());
	shared_ptr<KeyboardOut> keyboardOut = shared_ptr<KeyboardOut>(new KeyboardOut());
	bool showFPS = true;
	bool pause = false;
	int FRAME_LIMIT = 60;
	int num_threads = std::thread::hardware_concurrency();
	shared_ptr<Render> render = shared_ptr<Render>(new Render());
	shared_ptr<Controls> controls = shared_ptr<Controls>(new Controls());
	shared_ptr<ObjectList> objects = shared_ptr<ObjectList>(new ObjectList());
	Pool threadPool;

	shared_ptr<Scene> ActiveScenes[30];
	int numberOfScenes = 0;
	RenderWindow* window;


	void start();

	void addScene(shared_ptr<Scene> scene) {
		ActiveScenes[numberOfScenes] = scene;
		numberOfScenes++;
	}
	void removeScene(shared_ptr<Scene> scene) {
		bool move = false;
		for (int i = 0; i < numberOfScenes; i++) {
			if (ActiveScenes[i] == scene && !move) {
				ActiveScenes[i] = NULL;
				move = true;
			}
			else if (move) {
				ActiveScenes[i - 1] = ActiveScenes[i];
				ActiveScenes[i] = NULL;
			}
		}
		numberOfScenes--;
	}
};
