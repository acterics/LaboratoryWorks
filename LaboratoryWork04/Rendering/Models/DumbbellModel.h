#pragma once
#include "Model.h"
#include <time.h>
#include <stdarg.h>

#define DEFAULT_SPHERE_WIDTH 3.7f
#define DEFAULT_DUMBBELL_LENGTH 5
#define DEFAULT_DUMBBELL_RADIUS 2
#define DEFAULT_DUMBBELL_SMOOTHNESS 360



namespace Engine
{
	namespace Rendering
	{
		namespace Models
		{

			class DumbbellModel : public Model
			{
			public:
				DumbbellModel();
				DumbbellModel(float radius, float sphereWid, float dubbLen);
				DumbbellModel(float radius, float sphereWid, float dubbLen, unsigned int smooth);
				DumbbellModel(glm::vec3 position, float rad, float sphereWid, float dubbLen, unsigned int smooth);
				~DumbbellModel();

				void create();
				virtual void draw(const glm::mat4& projection_matrix,
					const glm::mat4& view_matrix) override final;
				virtual void update() override final;

			private:
				unsigned int smoothness;
				float radius;
				float sphereWidth;
				float dumbbellLength;
				unsigned int vertexCount;
				float angle;
				time_t timer;
			};
		}
	}
}