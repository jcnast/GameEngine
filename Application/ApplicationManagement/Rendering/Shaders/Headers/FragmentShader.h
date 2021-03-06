#pragma once

#include "ShaderBase.h"

#include "Core/Headers/PtrDefs.h"

#include "Dependencies\Includes\GLEW\glew.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto fragment shader information
		struct FragmentShader : ShaderBase
		{
			FragmentShader()
				: ShaderBase("FragmentShader", GL_FRAGMENT_SHADER)
			{}

			Ptr<const char> GetShader() const override;

			virtual void Prepare() const;
			virtual void CleanUp() const;

		protected:
			static Ptr<const char> Shader;
		};
	}
}