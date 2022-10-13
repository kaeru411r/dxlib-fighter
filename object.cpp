#include "object.h"

namespace ike {
	Object::Object() {
	}

	Object::~Object() {
	}


	bool ike::Object::update(const float deltaTime) {
		for (ike::Component* c : components_) {
			c->update(deltaTime);
		}
		return true;
	}

	bool ike::Object::addComponent(ike::Component* component) {
		components_.emplace_back(component);
		return true;
	}
	bool ike::Object::removeComponent(ike::Component* component) {
		if (components_.empty()) {
			return false;
		}
		auto it = components_.begin();
		while (it != components_.end()) {
			if ((*it) == component) {
				components_.erase(it);
				return true;
			}
			it++;
		}
		return false;
	}
}