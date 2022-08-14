#include "meshTransform.h"


ike::MeshTransform::MeshTransform(dxe::Mesh* mesh) {
	mesh_ = mesh;
}


void ike::MeshTransform::setPosition(const tnl::Vector3 position) {
	ike::Transform::setPosition(position);
	mesh_->pos_ = getPosition();
}


void ike::MeshTransform::eulerRotate(const tnl::Vector3 value) {
	ike::Transform::eulerRotate(value);
	mesh_->rot_q_ = getRotation();
}




void ike::MeshTransform::ownEulerRotate(const tnl::Vector3 value) {
	ike::Transform::ownEulerRotate(value);
	mesh_->rot_q_ = getRotation();
}