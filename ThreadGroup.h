#pragma once

#include <thread>
#include <atomic>

class ThreadGroup
{
public:
	ThreadGroup(unsigned int max) : max_(max), running_(0) { }

	~ThreadGroup() {
		while(running_.load() > 0)
			std::this_thread::yield();
	}

	void add(void f(void*), void* arg)
	{
		while(running_.load() >= max_)
			std::this_thread::yield();

		running_++;

		std::thread th([this,f,arg](){
				Raii raii(*this); // will decrement when destroyed
				f(arg);
			});

		th.detach();
	}

private:
	unsigned int max_;
	std::atomic<unsigned int> running_;

	struct Raii {
		Raii(ThreadGroup& tg) : tg_(tg) { }
		~Raii() { tg_.running_--; }
		ThreadGroup& tg_;
	};

	ThreadGroup(ThreadGroup&) = delete;
	void operator=(ThreadGroup&) = delete;
};


