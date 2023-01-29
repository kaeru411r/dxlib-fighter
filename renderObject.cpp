#pragma once
#include "renderObject.h"
//#include "component.h"


ike::RenderObject::RenderObject(dxe::Mesh* mesh) {
	transform_ = std::dynamic_pointer_cast<ike::MeshTransform>(ike::MeshTransform::Create(/*mesh*/));
}

ike::RenderObject::~RenderObject() {
	transform_.reset();
}


std::shared_ptr<ike::MeshTransform> ike::RenderObject::getTransform() const {
	return transform_;
}


bool ike::RenderObject::render(const dxe::Camera* camera) {
	transform_->render(camera);
	return true;
}
