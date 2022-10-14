#include "object.h"

namespace ike {
	Object::Object() {
	}

	Object::~Object() {
		deleteAllComponents();
	}


	bool ike::Object::update(const float deltaTime) {
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


	void ike::Object::deleteAllComponents() {
		for (int i = 0; i < components_.size(); ++i) {
			delete(components_[i]);
		}
		components_.clear();
	}
}