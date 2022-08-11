#include "object .h"
using namespace ike;

Object::Object(dxe::Mesh* mesh) {
	transform = new ike::MeshTransform(mesh);
}

Object::~Object() {
	delete(transform);
}