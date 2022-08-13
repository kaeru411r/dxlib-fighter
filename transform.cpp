#include "transform.h"

//using namespace ike;

ike::Transform::Transform() {
}
ike::Transform::Transform(dxe::Mesh* mesh) {
	meshes_.push_back(mesh);
}
ike::Transform::Transform(const std::list<dxe::Mesh*> meshes) {
	meshes_ = meshes;
}
ike::Transform::~Transform() {
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
tnl::Vector3 ike::Transform::getScale() const {
	return scale_;
}
void ike::Transform::Transform::setScale(const tnl::Vector3 scale) {
	tnl::Vector3 f = { scale.x / scale_.x, scale.y / scale_.y , scale.z / scale_.z };
	scale_ = scale;
	for (ike::Transform* t : getChildren()) {
		t->followScale(f);
	}
}



bool ike::Transform::setParent(Transform* data) {
	ike::Tree::setParent(data);
}

ike::Transform* ike::Transform::getParent() const {
	return static_cast<Transform*>(ike::Tree::getParent());
}
std::list<ike::Transform*> ike::Transform::getChildren() const {
	std::list<ike::Transform*> list;
	for (ike::Tree* t : ike::Tree::getChildren()) {
		list.push_back(static_cast<ike::Transform*>(t));
	}
	return list;
}

bool ike::Transform::childrenContains(const Transform* data) {
	return ike::Tree::childrenContains(data);
}
bool ike::Transform::allChildrenContains(const Transform* data) {
	return ike::Tree::allChildrenContains(data);
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


void ike::Transform::localEulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(tnl::Vector3::Normalize(value), rotation_);
	eulerRotate(axis * value.length());
}

void ike::Transform::localMove(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, rotation_);
	move(axis);
}

void ike::Transform::eulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	rotation_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), tnl::ToRadian(value.length()));
}

void ike::Transform::move(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	position_ += value;
	for (ike::Transform* tr : getChildren()) {
		tr->move(value);
	}
}

void ike::Transform::followRotate(const tnl::Vector3 value) {

}

void ike::Transform::followMove(const tnl::Vector3 value) {
	move(value);
}

void ike::Transform::followScale(const tnl::Vector3 value) {
	tnl::Vector3 s = { scale_.x * value.x, scale_.y * value.y , scale_.z * value.z };
	tnl::Vector3 pp = getParent()->getPosition();
	tnl::Vector3 lp = position_ - pp;
	tnl::Vector3 lp2 = { lp.x * value.x, lp.y * value.y , lp.z * value.z };
	localMove(lp2 - lp);
	setScale(s);
}