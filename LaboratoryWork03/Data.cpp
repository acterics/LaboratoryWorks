#include "Data.h"

Data::Data()
{
}

Data::Data(Data & data) :
	messages(messages)
{
}

Data::~Data()
{
}

int Data::getData()
{
	std::lock_guard<std::mutex> mutex(access);

	if (messages.empty())
		return -1;

	int data = messages.front();
	messages.pop();

	return data;
}

void Data::addData(int data)
{
	std::lock_guard<std::mutex> mutex(access);
	messages.push(data);
}

void Data::lock()
{
	access.lock();
}

void Data::unlock()
{
	access.unlock();
}
