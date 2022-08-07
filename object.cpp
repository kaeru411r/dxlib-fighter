#include "object .h"
using namespace ike;

Object::Object(dxe::Mesh* mesh) {
	transform = new ike::Transform();
}

Object::~Object() {
	delete(transform);
}