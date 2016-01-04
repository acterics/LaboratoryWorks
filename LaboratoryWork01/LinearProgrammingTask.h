#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
using namespace std;
class LinearProgrammingTask
{
public:
	enum Target			{MIN, MAX};
	enum RelationType	{MORE, EQUAL, LESS};

	Target							target;		
	vector<double>					targetFunction;
	vector<int> 					nonBasis;
	vector<int>						basis;			
	vector<vector<double>>			conditionMatrix;	
	vector<RelationType>			relations;
	bool							hasResult;
	int								targetVariableCount;


	LinearProgrammingTask();
	LinearProgrammingTask(vector<double> func, Target target, vector<vector<double>> matrix, vector<RelationType> relations);
	~LinearProgrammingTask();
	vector<double> result();

	vector<double> stepResult();


	void printSimplexTable();
	void clear();
	int findVariable(int value, vector<int> vector);
	bool methodStep(int &changedVariable1, int &changedVariable2);
	bool optimalMethodStep(int &changedVariable1, int &changedVariable2);
	void erase(int row, int column);
	void swapColumns(int column1, int column2);
	
private:
	int optimalLeadRow(int leadColumn);
	int optimalLeadColumn();
	int validLeadRow();
	int validLeadColumn(int leadRow);
	void transformSimplexTable(int leadRow, int leadColumn);
	void findValidValues();
	void findOptimalValues();
};

