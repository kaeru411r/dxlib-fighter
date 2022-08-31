#include "meshTransform.h"
#include "game_main.h"


ike::MeshTransform::MeshTransform(dxe::Mesh* mesh) {
	mesh_ = mesh;
}


void ike::MeshTransform::setPosition(const tnl::Vector3 position) {
	ike::Transform::setPosition(position);
	mesh_->pos_ = getPosition();
}


void ike::MeshTransform::setLocalPosition(const tnl::Vector3 position) {
	ike::Transform::setLocalPosition(position);
	mesh_->pos_ = getPosition();
}


void ike::MeshTransform::setLocalRotation(const tnl::Quaternion rotation) {
	ike::Transform::setLocalRotation(rotation);
	mesh_->rot_q_ = getRotation();
}


void ike::MeshTransform::setLocalScale(const tnl::Vector3 scale) {
	ike::Transform::setLocalScale(scale);
	mesh_->pos_ = getPosition();
	mesh_->scl_ = getScale();
}


void ike::MeshTransform::render(const dxe::Camera* camera) {
	mesh_->pos_ = getPosition();
	mesh_->rot_q_ = getRotation();
	mesh_->scl_ = getScale();
	mesh_->render(camera);
}

void ike::MeshTransform::eulerRotate(const tnl::Vector3 value) {
	ike::Transform::eulerRotate(value);
	mesh_->rot_q_ = getRotation();
}




void ike::MeshTransform::ownEulerRotate(const tnl::Vector3 value) {
	ike::Transform::ownEulerRotate(value);
	mesh_->rot_q_ = getRotation();
}