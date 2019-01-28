#include "ApplicationManagement/Geometric/Headers/World.h"

#include "ApplicationManagement/Geometric/Headers/CameraNode.h"

namespace Application
{
	namespace Geometric
	{
		World::World(Ptr<State> parentState)
			: Scene(parentState)
		{
			AddChild<CameraNode>(1024.0f / 800.0f);
		}
	}
}