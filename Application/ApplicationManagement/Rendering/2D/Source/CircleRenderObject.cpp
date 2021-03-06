#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

#include "Core/Math/Headers/UtilityFunctions.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Geometric;

namespace Application
{
	namespace Rendering
	{
		CircleRenderObject::CircleRenderObject(Core::Ptr<RenderManager> manager, Ptr<Transform> renderTransform, Color color)
			: CircleRenderObject(manager, renderTransform, color, 1.0f)
		{}

		CircleRenderObject::CircleRenderObject(Core::Ptr<RenderManager> manager, Ptr<Transform> renderTransform, Color color, float radius)
			: RenderObjectBase(manager, renderTransform, color)
			, Radius(radius)
			, Shader(manager->ObjectShaderManager.DefaultShader)
		{
			Initialize();
		}

		CircleRenderObject::~CircleRenderObject()
		{
			Vao.Delete();
			for (int i = 0; i < Vbos.size(); i++)
			{
				Vbos[i].Delete();
			}
		}

		void CircleRenderObject::Initialize()
		{
			// we want the circles drawn to be centered around the point. Any positional changed come from the transformation matrix
			Float3 center = 0.0f;
			float halfStepCount = 50.0f;

			auto createVertices = [this, center, halfStepCount](bool positiveY)
			{
				float startX = positiveY ? center.X - Radius : center.X + Radius;
				float endX = positiveY ? center.X + Radius : center.X - Radius;

				Float3 normal = Float3(0.0f);
				Float3 currentPosition = Float3{ startX, center.Y, 0.0f };
				for (float i = 1.0f; i <= halfStepCount; i++)
				{
					Push(Vertices, { currentPosition, normal });

					currentPosition.X = Lerp(startX, endX, i / halfStepCount);
					currentPosition.Y = positiveY ? Sqrt(Sqr(Radius) - Sqr(currentPosition.X)) : -Sqrt(Sqr(Radius) - Sqr(currentPosition.X));

					Push(Vertices, { currentPosition, normal });
					Push(Vertices, { center, normal });
				}
			};

			createVertices(true);
			createVertices(false);

			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			glBufferData(newBuffer.Type, Vertices.size() * sizeof(Data::Rendering::SimpleVertexDataBase), &Vertices[0], GL_STATIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::SimpleVertexDataBase), (void*)(0));
			// normal
			glEnableVertexAttribArray(1); // this matches with object shader construction
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::SimpleVertexDataBase), (void*)(offsetof(Data::Rendering::SimpleVertexDataBase, Data::Rendering::SimpleVertexDataBase::Position)));

			Vao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(Vbos, newBuffer);
		}

		void CircleRenderObject::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Vao.Bind();
			Shader.Prepare(mvp, color);
		}

		void CircleRenderObject::CleanUp() const
		{
			Vao.Unbind();
			Shader.CleanUp();
		}
	}
}