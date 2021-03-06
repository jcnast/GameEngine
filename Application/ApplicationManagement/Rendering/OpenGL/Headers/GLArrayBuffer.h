#pragma once

#include "GLObject.h"

namespace Application
{
	namespace Rendering
	{
		struct GLArrayBuffer : GLObject
		{
			GLArrayBuffer();
			GLArrayBuffer(GLuint object, GLenum type = GL_ARRAY_BUFFER);

			~GLArrayBuffer();

			void Generate();

			void Bind() const;

			void Unbind() const;

			void Delete();
		};
	}
}