#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct BoxRenderObject : RenderObjectBase
		{
			GLArrayBuffer Vao;
			Core::List<GLBuffer> Vbos;
			Core::List<Data::Rendering::SimpleVertexDataBase> Vertices;

			BoxRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color);
			BoxRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color, float width, float height);
			BoxRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color, Core::Math::Float2 scale);

			~BoxRenderObject();

			virtual void Initialize();

			virtual void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const;
			virtual void CleanUp() const;

			Core::size GetVertexCount() const override
			{
				return Vertices.size();
			}

		protected:
			ObjectShader& Shader;

			Float2 Scale;
		};
	}
}