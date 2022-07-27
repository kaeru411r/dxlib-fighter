#include "transform.h"

//using namespace ike;

ike::Transform::Transform(dxe::Mesh* mesh) {
	this->mesh_ = mesh;
}
ike::Transform::~Transform() {
	delete(mesh_);
	setParent(nullptr);
	removeAllChildren();
}

tnl::Vector3 ike::Transform::getPosition() const {
	return mesh_->pos_;
}
void ike::Transform::setPosition(const tnl::Vector3 position) {
	mesh_->pos_ = position;
}
tnl::Quaternion ike::Transform::getRotation() const {
	return mesh_->rot_q_;
}
void ike::Transform::setRotation(const tnl::Quaternion rotation) {
	mesh_->rot_q_ = rotation;
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
	return tnl::Vector3::TransformCoord(tnl::Vector3::up, mesh_->rot_q_);
}
tnl::Vector3 ike::Transform::left() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::left, mesh_->rot_q_);
}
tnl::Vector3 ike::Transform::front() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::front, mesh_->rot_q_);
}


void ike::Transform::localRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(tnl::Vector3::Normalize(value), mesh_->rot_q_);
	Rotate(axis * value.length());
}

void ike::Transform::localMove(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, mesh_->rot_q_);
	mesh_->pos_ += axis;
}

void ike::Transform::Rotate(const tnl::Vector3 value) {
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), tnl::ToRadian(value.length()));
}
