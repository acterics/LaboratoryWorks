#pragma once
#include <mutex>
class Event
{
private:
	std::mutex access;
	bool state;
public:
	Event() : state(false) {};
	~Event() {};
	void setEvent() { std::lock_guard<std::mutex> mutex(access); state = true; }
	void resetEvent() { std::lock_guard<std::mutex> mutex(access); state = false; }
	bool getState() { std::lock_guard<std::mutex> mutex(access); return state; }
};