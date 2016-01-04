#include "stdafx.h"
#include "LinearProgrammingTask.h"
#include "DaltonMethod.h"
#include <iostream>
int main()
{
	vector<vector<double>>						matrix = { { -1, 4, 12 },
														 { 4, -1, 12 } };

	vector<double>								func = { 1, 1, 0 };

	vector<LinearProgrammingTask::RelationType> relations = {
		LinearProgrammingTask::LESS,
		LinearProgrammingTask::LESS
	};

	LinearProgrammingTask::Target				target = LinearProgrammingTask::MAX;

	vector <vector<double >> valid = { { 0, 1, 4 },
									 { 0, 1, 3, 5 }, };



	DaltonMethod task(func, target, matrix, relations, valid);
	vector<double> result = task.result();
	for (auto element : result)
		cout << element << " ,";
    return 0;



}

