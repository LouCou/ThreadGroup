#ifndef THREADGROUP_H_
#define THREADGROUP_H_

#include <list>
#include <thread>
#include <atomic>
#include <algorithm>

class ThreadWrapper;
void run(ThreadWrapper* that, void f(void*), void* arg);

class ThreadWrapper
{
public:
	ThreadWrapper(void f(void*), void* arg)
		: finished_(false),
		  thread_(std::thread(run, this, f, arg))
	{
	}

	~ThreadWrapper()
	{
		if(thread_.joinable())
			thread_.join();
	}

	bool finished() const { return finished_; }
	void setFinished() { finished_ = true; }

private:
	std::atomic<bool> finished_;
	std::thread thread_;
};

void run(ThreadWrapper* that, void f(void*), void* arg)
{
	f(arg);
	that->setFinished();
}

class ThreadGroup
{
public:
	ThreadGroup() : counter_(0), max_(5) {}

	~ThreadGroup()
	{
		std::list<ThreadWrapper*>::iterator it = threads_.begin();
		while(it != threads_.end())
		{
			delete *it;
			++it;
		}
	}

	void add(void f(void*), void* arg)
	{
		ThreadWrapper* th = new ThreadWrapper(f, arg);
		threads_.push_back(th);

		if(++counter_ >= max_)
			cleanUp();
	}

	void cleanUp()
	{
		if(threads_.empty())
			return;

		size_t previousSize = threads_.size();

		std::list<ThreadWrapper*>::iterator it = threads_.begin();

		while(it != threads_.end())
		{
			if((*it)->finished())
			{
				delete *it;
				it = threads_.erase(it);
			}
			else
				++it;
		}

		if(previousSize != threads_.size())
			std::cout << "Cleanup: " << previousSize << "->" << threads_.size() << std::endl;
	}

private:
	std::list<ThreadWrapper*> threads_;
	size_t counter_, max_;
};



#endif /* THREADGROUP_H_ */
