#ifndef THREADGROUP_H_
#define THREADGROUP_H_

#include <list>
#include <thread>
#include <atomic>


class ThreadGroup
{
	class ThreadWrapper
	{
	public:
		ThreadWrapper(void f(void*), void* arg)
			: finished_(false)
			, thread_( [this, f, arg]{ f(arg); this->setFinished(); })
		{ }

		~ThreadWrapper()
		{
			if(thread_.joinable())
				thread_.join();
		}

		bool finished() const { return finished_.load(); }
		void setFinished() { finished_ = true; }

	private:
		std::atomic<bool> finished_;
		std::thread thread_;
	};

public:
	ThreadGroup(size_t maxThreads = 5) : maxThreads_(maxThreads) {}

	ThreadGroup(ThreadGroup&) = delete;
	void operator=(ThreadGroup&) = delete;

	void add(void f(void*), void* arg)
	{
		while(threads_.size() >= maxThreads_) {
			threads_.remove_if( [](auto& ptw){ return ptw->finished(); } );
			std::this_thread::yield();
		}

		threads_.emplace_back(new ThreadWrapper(f, arg));
		std::cout << "number of threads: " << threads_.size() << std::endl;
	}

private:
	std::list< std::unique_ptr<ThreadWrapper> > threads_;
	size_t maxThreads_;
};



#endif /* THREADGROUP_H_ */
