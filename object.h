#pragma once
#include "component.h"
#include <vector>
#include "iUpdate.h"

namespace ike {
	class Object : public ike::IUpdate {

	public:

		Object();
		virtual ~Object();

		virtual bool update(const float deltaTime);

		bool addComponent(ike::Component* component);
		bool removeComponent(ike::Component* component);

	private:

		void deleteAllComponents();

		std::vector<ike::Component*> components_;
	};
}