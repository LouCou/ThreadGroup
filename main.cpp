#include <iostream>
#include <thread>
#include <chrono>

#include "ThreadGroup.h"

struct Cat
{
	Cat(const std::string& s, int i) : name_(s), lives_(i) {}

	std::string name_;
	int lives_;
};

void handle(void* arg)
{
	Cat * cat = (Cat*) arg;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Cat " << cat->name_ << " has already lived " << cat->lives_ << " lives." << std::endl;
	delete cat;
}

int main()
{
	{
		ThreadGroup group;

		for(int i=0; i<30; ++i)
		{
			Cat * cat = new Cat("miaou", i);
			group.add(handle, cat);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

	std::cout << "enter a letter to quit. " << std::flush;
	char c; std::cin >> c;
}
