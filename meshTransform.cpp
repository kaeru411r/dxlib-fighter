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


void ike::MeshTransform::localMove(const tnl::Vector3 value) {
	ike::Transform::localMove(value);
	mesh_->pos_ = getPosition();
}


void ike::MeshTransform::localEulerRotate(const tnl::Vector3 value) {
	ike::Transform::localEulerRotate(value);
	mesh_->rot_q_ = getRotation();
}