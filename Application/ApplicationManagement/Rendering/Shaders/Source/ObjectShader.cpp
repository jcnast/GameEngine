#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> ObjectShader::Name = "ObjectShader";

		void ObjectShader::Prepare(const Float4x4& mvp, const Color& color)
		{
			VShader.Prepare(mvp, color);
			FShader.Prepare();

			ObjectShaderBase::Prepare();
		}

		void ObjectShader::CleanUp()
		{
			VShader.CleanUp();
			FShader.CleanUp();

			ObjectShaderBase::CleanUp();
		}

		void ObjectShader::Initialize()
		{

		}

		void ObjectShader::Destroy()
		{
			glDetachShader(Object, VShader.Object);
			glDetachShader(Object, FShader.Object);

			ObjectShaderBase::Destroy();
		}
	}
}