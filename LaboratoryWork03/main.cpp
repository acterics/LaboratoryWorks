#include <vector>
#include "Reader.h"
#include <time.h>
#include<chrono>
#include <conio.h>

void generate(Data& data, Event& exitEvent, int num)
{
	srand(num);
	while(!exitEvent.getState())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		data.addData(0 + rand() % 10);
	}	
}

void exitThread(Event& exitEvent, std::mutex &out)
{
	while (true)
	{
		if (_getch() == 'q')
		{
			exitEvent.setEvent();
			return;
		}
	}
	
}

int main()
{
	srand(time(0));
	std::mutex out;
	Data resourse;
	Event exitEvent;
	std::vector<Reader> wThreads;
	std::vector<std::thread> gThreads;
	wThreads.resize(3);
	gThreads.resize(2);

	std::thread eth(exitThread, std::ref(exitEvent), std::ref(out));
		for (unsigned int i = 0; i < gThreads.size(); i++)
			gThreads[i] = std::thread(generate, std::ref(resourse), std::ref(exitEvent), rand()%10);

		for (unsigned int i = 0; i < wThreads.size(); i++)
			wThreads[i].run(std::ref(resourse), std::ref(out), std::ref(exitEvent));

		eth.join();

		for (unsigned int i = 0; i < gThreads.size(); i++)
			gThreads[i].join();

		for (unsigned int i = 0; i < wThreads.size(); i++)
			wThreads[i].join();
		
		for (unsigned int i = 0; i < wThreads.size(); i++)
			wThreads[i].printStats(i);
	system("pause");
	return 0;
}