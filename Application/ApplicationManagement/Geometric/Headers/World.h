#pragma once

#include "ApplicationManagement/Geometric/Headers/Scene.h"
#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

namespace Application
{
	namespace Geometric
	{
		// a world is a scene, but it also has a camera (and probably more stuff in the future)
		struct World : Scene
		{
		protected:
			SharedPtr<CameraNode> WorldCamera;
		};
	}
}