#pragma once

#include "ObjectShaderBase.h"

#include "FragmentShader.h"
#include "DebugVertexShader.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Dependencies\Includes\GLEW\glew.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds onto name (for reflection) and a pixel/vertex shader combination
		struct DebugObjectShader : ObjectShaderBase
		{
			/*
			perhaps I can use the R() function to build up the shaders out or parts. each actual shader would have a
			reference to a static fragment/vertex shader and would load in the various parts to create the full code out of each bit and piece

			The above can be done, but it the parts will need to be broken up into (for each vertex and fragment shader) a 'declarations' part,
			to define the variables, and a 'use' part, to actually make use of the variables.

			Then, we will need to create a base shader to do all the 'must have' declarations and such and insert the subelements when building the shader
			*/

			DebugObjectShader() = default;

			Ptr<const char> GetName() override;

			Ptr<ShaderBase> GetVertexShader() override;
			Ptr<ShaderBase> GetFragmentxShader() override;

			virtual void Prepare(const Math::Float4x4& mvp, const Math::Color& color) const;
			void CleanUp() const override;

			void Initialize() override;
			void Destroy() override;

		private:
			static Ptr<const char> Name;

			FragmentShader FShader;
			DebugVertexShader VShader;
		};
	}
}