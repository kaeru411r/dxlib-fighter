#include "renderObject.h"
#include "../dxlib_ext/dxlib_ext.h";

ike::RenderObject::RenderObject(dxe::Mesh* mesh) {
	transform_ = new ike::MeshTransform(mesh);
}

ike::RenderObject::~RenderObject() {
	delete(transform_);
}

void ike::RenderObject::update(float deltaTime) {

}

ike::Transform* ike::RenderObject::getTransform() const {
	return transform_;
}

void ike::RenderObject::render(const dxe::Camera* camera) {
	transform_->render(camera);
	
}