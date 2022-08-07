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
