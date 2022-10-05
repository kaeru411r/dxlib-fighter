#include "transform.h"

//using namespace ike;

ike::Transform::Transform() {
	localPosition_ = { 0, 0, 0 };
	localRotation_ = tnl::Quaternion();
	localScale_ = { 1, 1, 1 };
}
ike::Transform::~Transform() {
}



//-----------ポジション関連-----------------------


tnl::Vector3 ike::Transform::getPosition() const {
	if (getParent() != nullptr) {
		tnl::Vector3 parentScale = getParent()->getScale();
		tnl::Vector3 right = getParent()->right() * (getLocalPosition().x * parentScale.x);
		tnl::Vector3 up = getParent()->up() * (getLocalPosition().y * parentScale.y);
		tnl::Vector3 front = getParent()->front() * (getLocalPosition().z * parentScale.z);
		tnl::Vector3 pos = right + up + front;
		return getParent()->getPosition() + pos;
	}
	else {
		return getLocalPosition();
	}
}
void ike::Transform::setPosition(const tnl::Vector3 position) {
	if (getParent() != nullptr) {
		tnl::Vector3 pos = position - getParent()->getPosition();
		tnl::Vector3 parentScale = getParent()->getScale();
		float right = getParent()->right().x * (pos.x * parentScale.x);
		float up = getParent()->up().y * (pos.y * parentScale.y);
		float front = getParent()->front().z * (pos.z * parentScale.z);
		setLocalPosition({right, up, front});
	}
	else {
		setLocalPosition(position);
	}
}
tnl::Vector3 ike::Transform::getLocalPosition() const {
	return localPosition_;
}
void ike::Transform::setLocalPosition(const tnl::Vector3 position) {
	localPosition_ = position;
}




//-------------姿勢関連-------------------------------------


tnl::Quaternion ike::Transform::getRotation() const {
	if (getParent() != nullptr) {
		return tnl::Quaternion::Subtract(getLocalRotation(), getParent()->getRotation());
	}
	else {
		return getLocalRotation();
	}
}
void ike::Transform::setRotation(const tnl::Quaternion rotation) {
	if (getParent() != nullptr) {
		setLocalRotation(tnl::Quaternion::Subtract(getParent()->getRotation(), rotation));
	}
	else {
		setLocalRotation(rotation);
	}
}

tnl::Quaternion ike::Transform::getLocalRotation() const {
	return localRotation_;
}
void ike::Transform::setLocalRotation(const tnl::Quaternion rotation) {
	localRotation_ = rotation;
}

tnl::Vector3 ike::Transform::getEulerAngle() const {
	if (getParent() != nullptr) {
		return getParent()->getEulerAngle() + getLocalEulerAngle();
	}
	else {
		return getLocalEulerAngle();
	}
}
void ike::Transform::setEulerAngle(const tnl::Vector3 angle) {
	tnl::Quaternion rot = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, angle.x);
	rot *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, angle.y);
	rot *= tnl::Quaternion::RotationAxis({ 0, 0, 1 }, angle.z);
	setRotation(rot);
}


tnl::Vector3 ike::Transform::getLocalEulerAngle() const {
	return getLocalRotation().getEuler();
}
void ike::Transform::setLoaclEulerAngle(const tnl::Vector3 angle) {
	tnl::Quaternion rot = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, angle.x);
	rot *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, angle.y);
	rot *= tnl::Quaternion::RotationAxis({ 0, 0, 1 }, angle.z);
	setLocalRotation(rot);
}




//--------------------スケール関連--------------------------------------


tnl::Vector3 ike::Transform::getScale() const {
	if (getParent() != nullptr) {
		tnl::Vector3 parentScale = getParent()->getScale();
		return { parentScale.x * getLocalScale().x, parentScale.y * getLocalScale().y , parentScale.z * getLocalScale().z };
	}
	else {
		return getLocalScale();
	}
}

tnl::Vector3 ike::Transform::getLocalScale() const {
	return localScale_;
}
void ike::Transform::setLocalScale(const tnl::Vector3 scale) {
	localScale_ = scale;
}




//------------------親子関連--------------------------------------------


bool ike::Transform::setParent(Transform* data) {
	tnl::Vector3 pos = -data->getPosition();
	//tnl::Vector3 rot = -data->localRotation_.getEuler();
	if (getParent() != nullptr) {
		pos += getParent()->getPosition();
		//rot += getParent()->localRotation_.getEuler();
	}
	localPosition_ += pos;
	//localRotation_ *= 
	return ike::Tree::setParent(data);
}

ike::Transform* ike::Transform::getParent() const {
	return dynamic_cast<Transform*>(ike::Tree::getParent());
}
std::list<ike::Transform*> ike::Transform::getChildren() const {
	std::list<ike::Transform*> list;
	for (ike::Tree* t : ike::Tree::getChildren()) {
		list.push_back(dynamic_cast<ike::Transform*>(t));
	}
	return list;
}

bool ike::Transform::childrenContains(const Transform* data) {
	return ike::Tree::childrenContains(data);
}
bool ike::Transform::allChildrenContains(const Transform* data) {
	return ike::Tree::allChildrenContains(data);
}




//------------------オブジェクトの軸-----------------------------


tnl::Vector3 ike::Transform::up() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::up, getRotation());
}
tnl::Vector3 ike::Transform::right() const {
	return tnl::Vector3::TransformCoord(-tnl::Vector3::left, getRotation());
}
tnl::Vector3 ike::Transform::front() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::front, getRotation());
}




//-------------------移動関数---------------------------------------


void ike::Transform::move(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	clsDx();
	printfDx("%f, %f, %f\n", getPosition().x, getPosition().y, getPosition().z);
	printfDx("%f, %f, %f\n", value.x, value.y, value.z);
	setPosition(getPosition() + value);
}

void ike::Transform::ownMove(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	move(axis);
}



//------------------回転関数-------------------------------


void ike::Transform::eulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	setEulerAngle(getEulerAngle() + value);
	//setRotation(getRotation() * tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), value.length()));
}
void ike::Transform::ownEulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(tnl::Vector3::Normalize(value), getRotation());
	eulerRotate(axis * value.length());
}