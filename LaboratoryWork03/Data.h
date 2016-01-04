#pragma once
#include "Event.h"
#include <windows.h>
#include <queue>
#include <mutex>
class Data
{
	std::mutex access;
	std::queue<int> messages;
public:
	Data();
	Data(Data& data);
	~Data();
	int getData();
	void addData(int data);
	void lock();
	void unlock();
};