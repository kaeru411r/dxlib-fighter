#include "transform.h"

//using namespace ike;

ike::Transform::Transform() {
}
ike::Transform::~Transform() {
	setParent(nullptr);
	removeAllChildren();
}

tnl::Vector3 ike::Transform::getPosition() const {
	return position_;
}
void ike::Transform::setPosition(const tnl::Vector3 position) {
	position_ = position;
}
tnl::Quaternion ike::Transform::getRotation() const {
	return rotation_;
}
void ike::Transform::setRotation(const tnl::Quaternion rotation) {
	rotation_ = rotation;
}

void ike::Transform::setParent(Transform* data) {
	if (parent_ == data) {
		return;
	}
	if (parent_ != nullptr) {
		parent_->removeChild(this);
	}
	parent_ = data;
	if (data != nullptr) {
		if (!childrenContains(data)) {
			data->addChild(this);
		}
	}
}
void ike::Transform::addChild(Transform* data) {
	if (data == nullptr) {
		return;
	}
	if (!childrenContains(data)) {
		children_.emplace_back(data);
	}
}
void ike::Transform::removeChild(Transform* data) {
	if (children_.empty()) {
		return;
	}
	auto it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			children_.erase(it);
			break;
		}
		it++;
	}
}

void ike::Transform::removeAllChildren() {
	auto it = children_.begin();
	while (!children_.empty() || it != children_.end()) {
		std::list<Transform*>::iterator buf = it;
		if (!children_.empty()) {
			buf++;
		}
		(*it)->setParent(nullptr);
		it = buf;
	}
	children_.clear();
}

bool ike::Transform::childrenContains(const Transform* data) {
	if (data == nullptr) {
		return false;
	}
	std::list<Transform*>::iterator it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			return true;
		}
	}
	return false;
}


tnl::Vector3 ike::Transform::up() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::up, rotation_);
}
tnl::Vector3 ike::Transform::left() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::left, rotation_);
}
tnl::Vector3 ike::Transform::front() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::front, rotation_);
}


void ike::Transform::localRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(tnl::Vector3::Normalize(value), rotation_);
	Rotate(axis * value.length());
}

void ike::Transform::localMove(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, rotation_);
	Move(axis);
}

void ike::Transform::Rotate(const tnl::Vector3 value) {
	rotation_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), tnl::ToRadian(value.length()));
}

void ike::Transform::Move(const tnl::Vector3 value) {
	position_ += value;
}

void ike::Transform::followRotate(const tnl::Vector3 value) {

}
