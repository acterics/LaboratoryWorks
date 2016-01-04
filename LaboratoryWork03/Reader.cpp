#include "Reader.h"

void Reader::operator() (Data & data, std::mutex &out, Event& exitEvent)
{
	int value = -1;
	while (!exitEvent.getState())
	{
		value = data.getData();

		if (value != -1)
		{
			out.lock();
			std::cout << "ID:" << std::this_thread::get_id() << " get " << value << std::endl;
			out.unlock();
			counter++;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}

void Reader::run(Data & data, std::mutex &out, Event& exitEvent)
{
	thread = std::thread(std::ref(*this), std::ref(data), std::ref(out), std::ref(exitEvent));
}


void Reader::join()
{
	thread.join();
}

void Reader::printStats(int i)
{
	std::cout << "Thread " << i << " called " << counter << " times" << std::endl;
}

