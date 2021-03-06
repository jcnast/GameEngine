#include "ApplicationManagement/Rendering/Headers/CameraManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		CameraManager::CameraManager(Core::Ptr<RenderManager> manager)
			: _manager(manager)
		{}
	}
}