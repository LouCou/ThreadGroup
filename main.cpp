#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "ThreadGroup.h"

struct Cat
{
	Cat(const std::string& s, int i) : name_(s), lives_(i) {}

	std::string name_;
	int lives_;
};

void handle(void* arg)
{
	std::unique_ptr<Cat> cat( (Cat*) arg );
	// do something useful cat!
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main()
{
	ThreadGroup group(5);

	for(int i=0; i<15; ++i)
	{
		Cat * cat = new Cat("minou", i);
		group.add(handle, cat);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
