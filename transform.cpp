#include "transform.h"

//using namespace ike;

ike::Transform::Transform() {
}
ike::Transform::~Transform() {
}



//-----------ポジション関連-----------------------


tnl::Vector3 ike::Transform::getPosition() const {
	if (getParent() != nullptr) {
		tnl::Vector3 parentScale = getParent()->getScale();
		tnl::Vector3 pos = { getLocalPosition().x * parentScale.x, getLocalPosition().y * parentScale.y, getLocalPosition().z * parentScale.z };
		return getParent()->getPosition() + pos;
	}
	else {
		return getLocalPosition();
	}
}
void ike::Transform::setPosition(const tnl::Vector3 position) {
	tnl::Vector3 delta = position - position_;
	for (ike::Transform* tr : getChildren()) {
		tr->setPosition(tr->position_ + delta);
	}
	position_ = position;
}
tnl::Vector3 ike::Transform::getLocalPosition() const {
	return localPosition_;
}
void ike::Transform::setLocalPosition(const tnl::Vector3 position) {
	localPosition_ = position;
	void setLocalRotation(const tnl::Quaternion rotation);
}




//-------------姿勢関連-------------------------------------


tnl::Quaternion ike::Transform::getRotation() const {
	return tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(getEulerAngle()), getEulerAngle().length());
}
void ike::Transform::setRotation(const tnl::Quaternion rotation) {
	tnl::Vector3 delta = rotation.getEuler() - rotation_.getEuler();
	printfDx("%f, %f, %f\n", delta.x, delta.y, delta.z);

	for (ike::Transform* tr : getChildren()) {
		tr->eulerRotate(delta);
	}
	rotation_ = rotation;
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
tnl::Vector3 ike::Transform::getLocalEulerAngle() const {
	return getLocalRotation().getEuler();
}



void ike::Transform::setLoaclEulerAngle(const tnl::Vector3 angle) {
	setLocalRotation(tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(angle), angle.length()));
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
void ike::Transform::setScale(const tnl::Vector3 scale) {
	tnl::Vector3 f = { scale.x / scale_.x, scale.y / scale_.y , scale.z / scale_.z };
	scale_ = scale;
	for (ike::Transform* t : getChildren()) {
		t->followScale(f);
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
	return tnl::Vector3::TransformCoord(tnl::Vector3::up, rotation_);
}
tnl::Vector3 ike::Transform::left() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::left, rotation_);
}
tnl::Vector3 ike::Transform::front() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::front, rotation_);
}




//-------------------移動関数---------------------------------------


void ike::Transform::move(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	setPosition(position_ + value);
}

void ike::Transform::ownMove(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, rotation_);
	move(axis);
}



//------------------回転関数-------------------------------


void ike::Transform::eulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	setRotation(rotation_ * tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), value.length()));
}
void ike::Transform::ownEulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(tnl::Vector3::Normalize(value), rotation_);
	eulerRotate(axis * value.length());
}




//--------------------親オブジェクトへの追従関数--------------------------------
void ike::Transform::followRotate(const tnl::Vector3 value) {

}

void ike::Transform::followPosition() {

}

void ike::Transform::followScale(const tnl::Vector3 value) {
	tnl::Vector3 s = { scale_.x * value.x, scale_.y * value.y , scale_.z * value.z };
	tnl::Vector3 lp = getLocalPosition();
	lp = { lp.x * value.x, lp.y * value.y , lp.z * value.z };
	setLocalPosition(lp);
	setScale(s);
}