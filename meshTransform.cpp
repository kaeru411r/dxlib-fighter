#include "meshTransform.h"


ike::MeshTransform::MeshTransform(dxe::Mesh* mesh) {
	mesh_ = mesh;
}

void ike::MeshTransform::move(const tnl::Vector3 value) {
	ike::Transform::move(value);
	mesh_->pos_ = getPosition();
}


void ike::MeshTransform::eulerRotate(const tnl::Vector3 value) {
	ike::Transform::eulerRotate(value);
	mesh_->rot_q_ = getRotation();
}


void ike::MeshTransform::ownMove(const tnl::Vector3 value) {
	ike::Transform::ownMove(value);
	mesh_->pos_ = getPosition();
}


void ike::MeshTransform::ownEulerRotate(const tnl::Vector3 value) {
	ike::Transform::ownEulerRotate(value);
	mesh_->rot_q_ = getRotation();
}