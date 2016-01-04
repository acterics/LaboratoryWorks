#include "stdafx.h"
#include "DaltonMethod.h"


DaltonMethod::DaltonMethod(vector<double> func, Target target, vector<vector<double>> matrix, vector<RelationType> relations, vector<vector<double>> valid) :
	LinearProgrammingTask(func, target, matrix, relations), validValues(valid)
{
}

DaltonMethod::~DaltonMethod()
{
}

vector<double> DaltonMethod::result()
{
	LinearProgrammingTask			particularResult;
	particularResult.target = this->target;
	particularResult.targetFunction = this->targetFunction;
	particularResult.conditionMatrix = this->conditionMatrix;
	particularResult.relations = this->relations;
	particularResult.basis = this->basis;
	particularResult.hasResult = true;
	particularResult.targetVariableCount = targetVariableCount;
	particularResult.printSimplexTable();

	vector<double>					result = particularResult.result();


	if (!particularResult.hasResult)
	{
		hasResult = false;
		return result;
	}

	while (particularResult.hasResult)
	{
		int r = -1;
		int t = -1;
		bool endLoop = false;
		for (int i = 0; i < targetVariableCount; i++)
		{
			if (endLoop)
				break;
			for (unsigned int j = 0; j < validValues[i].size() - 1; j++)
			{

				if (result[i] > validValues[i][j] &&
					result[i] < validValues[i][j + 1] && 
					result[i] != validValues[i][j] ||
					result[i] > validValues[i].back() ||
					result[i] < validValues[i].front())
				{
					r = i;
					t = j;
					endLoop = true;
					break;
				}
			}
		}
		if(r == -1)
			return result;

		int					m = particularResult.conditionMatrix.size();
		int					n = particularResult.targetFunction.size() - 1;
		vector<double>		additionalCondition;

		for (int i = 0; i < n; i++)
		{
			if (i < m)
				additionalCondition.push_back(0);
			else
				additionalCondition.push_back(-additionalVariable(r, i, t, particularResult));
		}
			
		additionalCondition.push_back(1);
		additionalCondition.push_back(-result[r] + validValues[r][t]);

		for (int i = 0; i < m; i++)
			particularResult.conditionMatrix[i].insert(particularResult.conditionMatrix[i].end() - 1, 0);


		particularResult.targetFunction.insert(particularResult.targetFunction.end() - 1, 0);

		particularResult.conditionMatrix.push_back(additionalCondition);

		particularResult.basis.push_back(n);

		int variable1 = -1,
			variable2 = -1;


		particularResult.printSimplexTable();

		while(particularResult.methodStep(variable1, variable2))
				result = particularResult.stepResult();
	}
	return result;
}

double DaltonMethod::additionalVariable(int r, int j, int t, LinearProgrammingTask task)
{
	int valuePosition;
	if ((valuePosition = task.findVariable(j, task.basis)) >= 0)
		return 0;
	valuePosition = task.findVariable(r, task.basis);
	if (task.conditionMatrix[valuePosition][j] >= 0)
		return task.conditionMatrix[valuePosition][j];
	else
		return -task.conditionMatrix[valuePosition][j] *
		(task.conditionMatrix[valuePosition].back() - validValues[valuePosition][t]) /
		(validValues[valuePosition][t + 1] - task.conditionMatrix[valuePosition].back());
}
