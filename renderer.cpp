#pragma once
#include "renderer.h"


ike::Renderer::Renderer(dxe::Mesh* mesh) {
	transform_ = new ike::MeshTransform(mesh);
}

ike::Renderer::~Renderer() {
	delete(transform_);
}


ike::Transform* ike::Renderer::getTransform() const {
	return transform_;
}


void ike::Renderer::render(const dxe::Camera* camera) {
	transform_->render(camera);
}
