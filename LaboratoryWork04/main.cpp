#pragma once
#include "CustomEngine.h"

using namespace Engine;
using namespace Rendering::Models;
int main(int argc, char **argv)
{
	CustomEngine* engine = new CustomEngine();
	engine->init(argc, argv);


	
	DumbbellModel* dumbbell = new DumbbellModel();
	dumbbell->setProgram(engine->getShaderManager()->getShader(DEFAULT_PROGRAM));
	dumbbell->create();
	engine->getModelManager()->setModel("dumbbell", dumbbell);
	engine->run();

	delete engine;
	return 0;
}