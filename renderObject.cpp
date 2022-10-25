#pragma once
#include "renderObject.h"
//#include "component.h"


ike::RenderObject::RenderObject(dxe::Mesh* mesh) {
	addComponent(new ike::MeshTransform(mesh));
}

ike::RenderObject::~RenderObject() {
	delete(transform_);
}


ike::Transform* ike::RenderObject::getTransform() const {
	return transform_;
}


void ike::RenderObject::render(const dxe::Camera* camera) {
	transform_->render(camera);
}
