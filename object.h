#pragma once
#include "component.h"
#include <vector>

namespace ike {
	class Object {

	public:

		Object();
		virtual ~Object();

		bool update(const float deltaTime);

		bool addComponent(ike::Component* component);
		bool removeComponent(ike::Component* component);

	private:

		void deleteAllComponents();

		std::vector<ike::Component*> components_;
	};
}