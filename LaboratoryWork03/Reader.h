#pragma once
#include <mutex>
#include <iostream>
#include <thread>
#include <string>
#include "Event.h"
#include "Data.h"
class Reader
{
	int counter;
	std::thread thread;
	
public:
	Reader() : counter(0) {};
	void run(Data& data, std::mutex& out, Event& exitEvent);
	void operator() (Data& data, std::mutex &out, Event& exitEvent);
	void join();
	void printStats(int i);
	
};