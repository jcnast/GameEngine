#include "ApplicationManagement\Geometric\Headers\ContentBase.h"

#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

namespace Application
{
	namespace Geometric
	{
		ContentBase::ContentBase(const Ptr<State> owningState)
			: EntityBase(owningState)
			, OnContainerDeleted([this]
		{
			Container = nullptr;
			return false;
		})
		{

		}

		ContentBase::~ContentBase()
		{
			ContentDeleted();
		}

		void ContentBase::SetContainer(Ptr<ContainerBase> parentContainer)
		{
			Container = parentContainer;

			Container->ContainerDeleted += OnContainerDeleted;
		}

		Ptr<ContainerBase> ContentBase::GetContainer() const
		{
			return Container;
		}
	}
}