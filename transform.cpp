#include "transform.h"

//using namespace ike;


ike::Transform::Transform() {
	tree_ = new ike::Tree<ike::Transform>(this);
	localPosition_ = { 0, 0, 0 };
	localRotation_ = tnl::Quaternion();
	localScale_ = { 1, 1, 1 };
}
ike::Transform::~Transform() {
	delete(tree_);
}



//-----------�|�W�V�����֘A-----------------------

		/// <summary>���݂�Position��Ԃ�</summary>
		/// <returns></returns>
tnl::Vector3 ike::Transform::getPosition() const {
	if (getParent() != nullptr) {

		return getParent()->toWarldPosition(getLocalPosition());
	}
	else {
		return getLocalPosition();
	}
}
void ike::Transform::setPosition(const tnl::Vector3 position) {
	if (getParent() != nullptr) {
		setLocalPosition(getParent()->toLocalPosition(position));
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




//-------------��]�֘A-------------------------------------


tnl::Quaternion ike::Transform::getRotation() const {
	if (getParent() != nullptr) {
		return getParent()->toWorldRotation(getLocalRotation());
	}
	else {
		return getLocalRotation();
	}
}
void ike::Transform::setRotation(const tnl::Quaternion rotation) {
	if (getParent() != nullptr) {
		setLocalRotation(getParent()->toLocalRotation(rotation));
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

#if EULER
tnl::Vector3 ike::Transform::getEulerAngle() const {
	if (getParent() != nullptr) {
		tnl::Vector3 angle = getParent()->getEulerAngle() + getLocalEulerAngle();
		angle = { abs(angle.x), abs(angle.y), abs(angle.z) };
		return angle;
	}
	else {
		return getLocalEulerAngle();
	}
}
void ike::Transform::setEulerAngle(const tnl::Vector3 angle) {
	//setRotation(eulerToQuaternion(angle));
	if (localRotation_.getEuler().length() != 0) {
		tnl::Vector3 vec = localRotation_.getEuler();
		setLocalRotation(tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(vec), vec.length()));
	}
}


tnl::Vector3 ike::Transform::getLocalEulerAngle() const {
	tnl::Vector3 angle = getLocalRotation().getEuler();
	angle = { tnl::ToDegree(angle.x), tnl::ToDegree(angle.y), tnl::ToDegree(angle.z) };
	angle = { abs(angle.x), abs(angle.y), abs(angle.z) };
	return angle;
}
void ike::Transform::setLocalEulerAngle(const tnl::Vector3 angle) {

	setLocalRotation(eulerToQuaternion(angle));
}

tnl::Quaternion ike::Transform::eulerToQuaternion(tnl::Vector3 euler) {
	tnl::Quaternion rot = tnl::Quaternion::RotationAxis(tnl::Vector3::front, tnl::ToRadian(euler.z));
	rot *= tnl::Quaternion::RotationAxis(tnl::Vector3::up, tnl::ToRadian(euler.y));
	rot *= tnl::Quaternion::RotationAxis(tnl::Vector3::right, tnl::ToRadian(euler.x));

	return rot;
}

#endif


//--------------------�X�P�[���֘A--------------------------------------


tnl::Vector3 ike::Transform::getScale() const {
	this;
	if (getParent() != nullptr) {
		tnl::Vector3 parentScale = getParent()->getScale();
		return { parentScale.x * getLocalScale().x, parentScale.y * getLocalScale().y , parentScale.z * getLocalScale().z };
	}
	else {
		return getLocalScale();
	}
}
void ike::Transform::setScale(const tnl::Vector3 scale) {
	if (getParent() != nullptr) {
		tnl::Vector3 parentScale = getParent()->getScale();
		setLocalScale({ scale.x / parentScale.y, scale.y / parentScale.x, scale.z / parentScale.z });
	}
	else {
		setLocalScale(scale);
	}
}

tnl::Vector3 ike::Transform::getLocalScale() const {
	return localScale_;
}
void ike::Transform::setLocalScale(const tnl::Vector3 scale) {
	localScale_ = scale;
}




//------------------�e�q�֘A--------------------------------------------


bool ike::Transform::setParent(Transform* parent) {
	if (getParent() != nullptr) {
		setLocalPosition(parent->toLocalPosition(getPosition()));
		setLocalScale(parent->toLocalScale(getScale()));
		setLocalRotation(parent->toLocalRotation(getRotation()));
	}
	else {
		setLocalPosition(getPosition());
		setLocalScale(getScale());
		setLocalRotation(getRotation());
	}
	return tree_->setParent(parent->tree_);
}

ike::Transform* ike::Transform::getParent() const {
	this;
	if (tree_->getParent() != nullptr) {
		return (ike::Transform*)(tree_->getParent()->getData());
	}
	else {
		return nullptr;
	}
}
std::list<ike::Transform*> ike::Transform::getChildren() const {
	std::list<ike::Transform*> list;
	for (ike::Tree<ike::Transform>* t : tree_->getChildren()) {
		list.push_back((ike::Transform*)t);
	}
	return list;
}

bool ike::Transform::childrenContains(const Transform* data) {
	return tree_->childrenContains((ike::Transform*)tree_);
}
bool ike::Transform::allChildrenContains(const Transform* data) {
	return tree_->allChildrenContains((ike::Transform*)tree_);
}




//------------------�I�u�W�F�N�g�̎�-----------------------------


tnl::Vector3 ike::Transform::up() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::up, getRotation());
}
tnl::Vector3 ike::Transform::right() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::right, getRotation());
}
tnl::Vector3 ike::Transform::front() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::front, getRotation());
}




//-------------------�ړ��֐�---------------------------------------


void ike::Transform::move(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	setPosition(getPosition() + value);
}

void ike::Transform::ownMove(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	//tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	move(axis);
}



//------------------��]�֐�-------------------------------

#if ROTATE
void ike::Transform::eulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	setRotation(getRotation() * tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), value.length() / 180 * tnl::PI));
}
void ike::Transform::ownEulerRotate(const tnl::Vector3 value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 vec = tnl::Vector3::TransformCoord(value, getLocalRotation());
	setLocalRotation(getLocalRotation() * tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(vec), vec.length() / 180 * tnl::PI));
}
#endif


//-----------------���W�n�ϊ�-------------------------------------------------

#if CONVERT
tnl::Vector3 ike::Transform::toWarldPosition(const tnl::Vector3& position) const {
	tnl::Vector3 scale = getScale();
	tnl::Vector3 right = this->right() * (position.x * scale.x);
	tnl::Vector3 up = this ->up() * (position.y * scale.y);
	tnl::Vector3 front = this->front() * (position.z * scale.z);
	tnl::Vector3 pos = right + up + front;
	return getPosition() + pos;
}
tnl::Vector3 ike::Transform::toLocalPosition(const tnl::Vector3& position) const {
	tnl::Vector3 scale = getScale();
	tnl::Vector3 worldRight = tnl::Vector3::right * tnl::Vector3::Dot(right(), position - getPosition()) / scale.x;
	tnl::Vector3 worldUp = tnl::Vector3::up * tnl::Vector3::Dot(up(), position - getPosition()) / scale.y;
	tnl::Vector3 worldFront = tnl::Vector3::front * tnl::Vector3::Dot(front(), position - getPosition()) / scale.z;
	tnl::Vector3 pos = worldRight + worldUp + worldFront;
	return pos;
}
tnl::Vector3 ike::Transform::toWarldScale(const tnl::Vector3& scale) const {
	tnl::Vector3 thisScale = getScale();
	return tnl::Vector3(thisScale.x * scale.x, thisScale.y * scale.y, thisScale.z * scale.z);
}
tnl::Vector3 ike::Transform::toLocalScale(const tnl::Vector3& scale) const {
	tnl::Vector3 thisScale = getScale();
	return tnl::Vector3(scale.x / thisScale.x, scale.y / thisScale.y, scale.z / thisScale.z);
}
tnl::Quaternion ike::Transform::toWorldRotation(const tnl::Quaternion& rotation) const noexcept{
	return tnl::Quaternion::Subtract(rotation, getRotation());
}
tnl::Quaternion ike::Transform::toLocalRotation(const tnl::Quaternion& rotation) const noexcept {
	return tnl::Quaternion::Subtract(getRotation(), rotation);
}
#endif