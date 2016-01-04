#pragma once
#include <string>
#include "LinearProgrammingTask.h"
using namespace std;
class DaltonMethod : public LinearProgrammingTask
{
public:
	vector<vector<double>>		validValues;
	DaltonMethod(vector<double> func, Target target, vector<vector<double>> matrix, vector<RelationType> relations, vector<vector<double>> valid);
	~DaltonMethod();
	vector<double> result();
private:
	double additionalVariable(int r, int j, int t, LinearProgrammingTask task);
};

