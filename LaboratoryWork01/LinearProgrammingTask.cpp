#include "stdafx.h"
#include "LinearProgrammingTask.h"


LinearProgrammingTask::LinearProgrammingTask()
{
}


LinearProgrammingTask::LinearProgrammingTask(vector<double> func, Target target, vector<vector<double>> matrix, vector<RelationType> relations) :
	relations(relations)
{
	targetVariableCount = func.size() - 1;
	int factor = 1;
	if (target == MAX)
		factor = -1;
	for (unsigned int i = 0; i < targetVariableCount + matrix.size(); i++)
	{
		if (i < func.size())
			targetFunction.push_back(func[i] * factor);
		else
			targetFunction.push_back(0);

	}

	targetFunction.push_back(func.back() * factor);
	int additionalVariable;
	vector<double> condition;
	for (unsigned int row = 0; row < matrix.size(); row++)
	{
		condition.clear();
		additionalVariable = row + func.size() - 1;
		basis.push_back(additionalVariable);
		if (this->relations[row] == LESS)
			factor = 1;
		else
			factor = -1;

		for (int j = 0; j < targetVariableCount + matrix.size(); j++)
		{
			if (j < targetVariableCount)
				condition.push_back(matrix[row][j] * factor);
			else
			{
				if (j == additionalVariable)
					condition.push_back(1);
				else
					condition.push_back(0);
			}
		}
		condition.push_back(matrix[row].back() * factor);
		conditionMatrix.push_back(condition);
	}
	hasResult = true;
}

LinearProgrammingTask::~LinearProgrammingTask()
{
}

vector<double> LinearProgrammingTask::result()
{
	vector<double> result;
	int factor = 1;
	findValidValues();

	if (!hasResult)
		return result;

	findOptimalValues();
	if (!hasResult)
		return result;

	return stepResult();
}

vector<double> LinearProgrammingTask::stepResult()
{
	int factor = 1;
	vector<double> result;
	int position;
	for (int i = 0; i < targetVariableCount; i++)
	{
		if ((position = findVariable(i, basis)) != -1)
			result.push_back(conditionMatrix[position].back());
		else
			result.push_back(0);
	}
	if (target == MAX)
		factor = -1;
	result.push_back(targetFunction.back() * factor);
	return result;
}


void LinearProgrammingTask::printSimplexTable()
{
	cout << "\t";
	for (unsigned int i = 0; i < conditionMatrix.front().size() - 1; i++)
		cout << "x" << i << "\t";
	cout << "b" << endl;


	for (auto row = conditionMatrix.begin(); row != conditionMatrix.end(); row++)
	{
		cout << "x" << basis[distance(conditionMatrix.begin(), row)] << "\t";
		for (vector<double>::iterator element = row->begin(); element != row->end(); element++)
			cout << fixed << setprecision(2) << *element << "\t";
		cout << endl;
	}

	cout << "F\t";
	for (auto element = targetFunction.begin(); element != targetFunction.end(); element++)
		cout << fixed << setprecision(2) << *element << "\t";
	cout << endl;
	for (int i = 0; i < 60; i++)
		cout << "*";
	cout << endl << endl;
}

void LinearProgrammingTask::clear()
{
	targetFunction.clear();
	nonBasis.clear();
	basis.clear();
	conditionMatrix.clear();
	relations.clear();
	hasResult = true;
}

int LinearProgrammingTask::findVariable(int value, vector<int> vector)
{
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == value)
			return i;
	}
	return -1;
}



int LinearProgrammingTask::optimalLeadRow(int leadColumn)
{
	int leadRow = -1;
	double marginalValue = LONG_MAX;
	for (unsigned int row = 0; row < conditionMatrix.size(); row++)
	{
		if (conditionMatrix[row].back() / conditionMatrix[row][leadColumn] < marginalValue && conditionMatrix[row][leadColumn] > 0 && conditionMatrix[row].back() > 0)
		{
			marginalValue = conditionMatrix[row].back() / conditionMatrix[row][leadColumn];
			leadRow = row;
		}
	}
	return leadRow;
}

int LinearProgrammingTask::optimalLeadColumn()
{
	int leadColumn = -1;
	double marginalValue = LONG_MIN;
	for (unsigned int column = 0; column < targetFunction.size() - 1; column++)
	{
		if (abs(targetFunction[column]) > marginalValue && targetFunction[column] < 0)
		{
			marginalValue = abs(targetFunction[column]);
			leadColumn = column;
		}
	}
	return leadColumn;
}

int LinearProgrammingTask::validLeadRow()
{
	double maxValue = LONG_MIN;
	int row = -1;
	for (auto element = conditionMatrix.begin(); element != conditionMatrix.end(); element++)
	{
		if (abs(element->back()) > maxValue && element->back() < 0)
		{
			maxValue = abs(element->back());
			row = distance(conditionMatrix.begin(), element);
		}
	}
	return row;
}

int LinearProgrammingTask::validLeadColumn(int leadRow)
{

	double maxValue = LONG_MIN;
	int column = -1;
	for (auto element = conditionMatrix[leadRow].begin(); element != conditionMatrix[leadRow].end() - 1; element++)
	{
		if (abs(*element) > maxValue && *element < 0)
		{
			maxValue = abs(*element);
			column = distance(conditionMatrix[leadRow].begin(), element);
		}
	}
	return column;
}

void LinearProgrammingTask::transformSimplexTable(int leadRowNumber, int leadColumnNumber)
{
	
	double leadElement = conditionMatrix[leadRowNumber][leadColumnNumber];
	vector<double>	leadRow,
					leadColumn;
	for (unsigned int i = 0; i < conditionMatrix[leadRowNumber].size(); i++)
	{
		if (findVariable(i, basis) < 0)
			leadRow.push_back(conditionMatrix[leadRowNumber][i]);
		else
			leadRow.push_back(0);
	}
	leadColumn.push_back(targetFunction[leadColumnNumber]);
	for (auto row : conditionMatrix)
		leadColumn.push_back(row[leadColumnNumber]);


	//Transformation for factors
	for (unsigned int i = 0; i < conditionMatrix.size(); i++)
	{

		for (unsigned int j = 0; j < conditionMatrix[i].size() - 1; j++)
		{
			if (findVariable(j, basis) >= 0)
				continue;
			if (i != leadRowNumber)
			{
				if (j != leadColumnNumber)
					conditionMatrix[i][j] -= (leadRow[j] * leadColumn[i + 1]) / leadElement;
				else
					conditionMatrix[i][j] *= -1 / leadElement;
			}
			else
			{
				if (j != leadColumnNumber)
					conditionMatrix[i][j] *= 1 / leadElement;
				else
					conditionMatrix[i][j] = 1 / leadElement;
			}
		}
	}
	//Transformation for free members
	for (unsigned int i = 0; i < targetFunction.size(); i++)
	{
		if (findVariable(i, basis) >= 0)
			continue;
		if (i != leadColumnNumber)
			targetFunction[i] -= (leadRow[i] * leadColumn[0]) / leadElement;
		else
			targetFunction[i] *= -1 / leadElement;
	}

	for (unsigned int i = 0; i < conditionMatrix.size(); i++)
	{
		if (i != leadRowNumber)
			conditionMatrix[i].back() -= (leadRow.back() * leadColumn[i + 1]) / leadElement;
		else
			conditionMatrix[i].back() *= 1 / leadElement;
	}
	swapColumns(leadColumnNumber, basis[leadRowNumber]);
	basis[leadRowNumber] = leadColumnNumber;
	printSimplexTable();
	
	
}

void LinearProgrammingTask::findValidValues()
{
	int leadRowNumber = validLeadRow();
	if(leadRowNumber == -1)
		return;
	int leadColumnNumber = validLeadColumn(leadRowNumber);
	if (leadColumnNumber == -1)
	{
		hasResult = false;
		return;
	}
	while (leadRowNumber != -1)
	{
		transformSimplexTable(leadRowNumber, leadColumnNumber);
		leadRowNumber = validLeadRow();
		if (leadRowNumber == -1)
			return;
		leadColumnNumber = validLeadColumn(leadRowNumber);
		if (leadColumnNumber == -1)
		{
			hasResult = false;
			return;
		}
	}
}

void LinearProgrammingTask::findOptimalValues()
{
	int leadColumn;
	int leadRow;
	do
	{
		leadColumn = optimalLeadColumn();

		if (leadColumn == -1)
			return;
		leadRow = optimalLeadRow(leadColumn);

		if (leadRow == -1)
		{
			hasResult = false;
			return;
		}

		transformSimplexTable(leadRow, leadColumn);

	} while ((leadColumn != -1));

}


bool LinearProgrammingTask::methodStep(int &changedVariable1, int &changedVariable2)
{
	int leadRowNumber = validLeadRow();

	if (leadRowNumber == -1)
		return optimalMethodStep(changedVariable1, changedVariable2);


	int leadColumnNumber = validLeadColumn(leadRowNumber);
	if (leadColumnNumber == -1)
	{
		hasResult = false;
		return false;
	}
	vector<int> oldBasis = basis;
	transformSimplexTable(leadRowNumber, leadColumnNumber);
	for (unsigned int i = 0; i < basis.size(); i++)
	{
		if (oldBasis[i] - basis[i])
		{
			changedVariable1 = oldBasis[i];
			changedVariable2 = basis[i];
			return true;
		}
	}
	return false;
}

bool LinearProgrammingTask::optimalMethodStep(int & changedVariable1, int & changedVariable2)
{
	int leadColumnNumber = optimalLeadColumn();
	if (leadColumnNumber == -1)
		return false;
	int leadRowNumber = optimalLeadRow(leadColumnNumber);
	if (leadRowNumber == -1)
	{
		hasResult = false;
		return false;
	}
	vector<int> oldBasis = basis;
	transformSimplexTable(leadRowNumber, leadColumnNumber);
	for (unsigned int i = 0; i < basis.size(); i++)
	{
		if (oldBasis[i] - basis[i])
		{
			changedVariable1 = oldBasis[i];
			changedVariable2 = basis[i];
			return true;
		}
	}
	return false;
}



void LinearProgrammingTask::erase(int row, int column)
{
	for (auto rowIterator = conditionMatrix.begin(); rowIterator != conditionMatrix.end(); rowIterator++)
		rowIterator->erase(rowIterator->begin() + column);
	conditionMatrix.erase(conditionMatrix.begin() + row);
	targetFunction.erase(targetFunction.begin() + column);
	basis.erase(basis.begin() + row);

}

void LinearProgrammingTask::swapColumns(int column1, int column2)
{
	for (unsigned int i = 0; i < conditionMatrix.size(); i++)
	{
		swap(conditionMatrix[i][column1], conditionMatrix[i][column2]);
	}
	swap(targetFunction[column1], targetFunction[column2]);
}

