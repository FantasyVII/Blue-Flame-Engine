#pragma once
#include <string>
#include "IComponent.h"
#include "BF/Common.h"

namespace BF
{
	namespace ECS
	{
		template <class T>
		class Component : public IComponent
		{
		public:
			Component(IComponent::Type type);
			virtual ~Component();
		};

#include "Component.inl"
	}
}