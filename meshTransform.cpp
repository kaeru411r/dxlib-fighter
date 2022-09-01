#include "meshTransform.h"
#include "game_main.h"


ike::MeshTransform::MeshTransform(dxe::Mesh* mesh) {
	mesh_ = mesh;
}


void ike::MeshTransform::render(const dxe::Camera* camera) {
	mesh_->pos_ = getPosition();
	mesh_->rot_q_ = getRotation();
	mesh_->scl_ = getScale();
	mesh_->render(camera);
}
