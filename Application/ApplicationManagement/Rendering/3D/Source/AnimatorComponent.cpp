#include "ApplicationManagement/Animation/Headers/AnimatorComponent.h"
#include "ApplicationManagement/Animation/Headers/Animator.h"

using namespace Core;

namespace Application
{
	namespace Animation
	{
		AnimatorComponent::AnimatorComponent(Core::Ptr<EntityBase> entity, Ptr<AnimationManager> animationManager)
			: Component<AnimatorComponent>(entity, this)
			, _animationManager(animationManager)
		{

		}

		Core::Ptr<IAnimator> AnimatorComponent::AddAnimator(Core::UniquePtr<IAnimator> animator)
		{
			return AddAnimator(_animationManager->AddAnimator(move(animator)));
		}

		Ptr<IAnimator> AnimatorComponent::AddAnimator(Ptr<IAnimator> animator)
		{
			Push(_animators, move(animator));

			return _animators[_animators.size() - 1];
		}

		void AnimatorComponent::RemoveAnimator(Core::Ptr<IAnimator> animator)
		{
			Remove(_animators, animator);
			_animationManager->RemoveAnimator(animator);
		}
	}
}