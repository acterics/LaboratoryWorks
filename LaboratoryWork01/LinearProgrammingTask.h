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
	vector<double>					targetFunction; //Factors of main funcion in the task
	vector<int> 					nonBasis; //Numbers of variables that is't exist in the basis
	vector<int>						basis; // Numbers of variables that's exist in the basis
	vector<vector<double>>			conditionMatrix; //List of limitation conditions of the task
	vector<RelationType>			relations; // Relations in limitation conditions of the task
	bool							hasResult; // False if task has no any result
	int								targetVariableCount; // Count of the variables in target function


	LinearProgrammingTask();
	LinearProgrammingTask(vector<double> func, Target target, vector<vector<double>> matrix, vector<RelationType> relations);
	~LinearProgrammingTask();

	//Resurns final result vector
	vector<double> result();

	//Returns result vector after single transfrmation
	vector<double> stepResult();
	void printSimplexTable();

	//Clear all task parametrs
	void clear();

	//Return number of variable with given value. If there's no such value - return -1
	int findVariable(int value, vector<int> vector);

	//One simplex table transformation
	bool methodStep(int &changedVariable1, int &changedVariable2);

	//One simplex table transformation when method has reached valid result
	bool optimalMethodStep(int &changedVariable1, int &changedVariable2);

	//Erasing row and column from simplex table
	void erase(int row, int column);

	//Swaps values in columns of simplex table
	void swapColumns(int column1, int column2);
	
private:

	//Return number of lead row when method has reached valid result
	int optimalLeadRow(int leadColumn);

	//Return number of lead column when method has reached valid result
	int optimalLeadColumn();

	//Return number of lead row when method hasn't reached valid result
	int validLeadRow();

	//Return number of lead column when method hasn't reached valid result
	int validLeadColumn(int leadRow);

	//Simplex table transformation
	void transformSimplexTable(int leadRow, int leadColumn);

	//Method reach valid result
	void findValidValues();

	//Method reach final result from valid one
	void findOptimalValues();
};

