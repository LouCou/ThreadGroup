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

		increment();

		std::thread th([this,f,arg](){
				RaiiDecrementor<ThreadGroup> raii(*this);
				f(arg);
			});

		th.detach();
	}

	void increment() { running_++; }
	void decrement() { running_--; }

private:
	unsigned int max_;
	std::atomic<unsigned int> running_;

	template<typename T>
	struct RaiiDecrementor {
		RaiiDecrementor(T& t) : t_(t) { }
		~RaiiDecrementor() { t_.decrement(); }
		T& t_;
	};

	ThreadGroup(ThreadGroup&) = delete;
	void operator=(ThreadGroup&) = delete;
};


