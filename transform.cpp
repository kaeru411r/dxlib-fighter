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



//-----------ポジション関連-----------------------

		/// <summary>現在のPositionを返す</summary>
		/// <returns></returns>
tnl::Vector3 ike::Transform::getPosition() const {
	if (getParent() != nullptr) {

		return getParent()->toWarldPosition(getLocalPosition());
	}
	else {
		return getLocalPosition();
	}
}
void ike::Transform::setPosition(const tnl::Vector3& position) {
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




//-------------回転関連-------------------------------------


tnl::Quaternion ike::Transform::getRotation() const {
	if (getParent() != nullptr) {
		return getParent()->toWorldRotation(getLocalRotation());
	}
	else {
		return getLocalRotation();
	}
}
void ike::Transform::setRotation(const tnl::Quaternion& rotation) {
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
void ike::Transform::setLocalRotation(const tnl::Quaternion& rotation) {
	localRotation_ = rotation;
}

#if EULER
tnl::Vector3 ike::Transform::getEulerAngle() const {
	if (getParent() != nullptr) {
		tnl::Vector3 angle = getParent()->getEulerAngle() + getLocalEulerAngle();
		//angle = { abs(angle.x), abs(angle.y), abs(angle.z) };
		return angle;
	}
	else {
		return getLocalEulerAngle();
	}
}
void ike::Transform::setEulerAngle(const tnl::Vector3 angle) {
	if (getEulerAngle() == angle) { return; }

	if (localRotation_.getEuler().length() != 0) {
		tnl::Vector3 vec = localRotation_.getEuler();
		setLocalRotation(tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(vec), vec.length()));
	}
}


tnl::Vector3 ike::Transform::getLocalEulerAngle() const {
	tnl::Vector3 angle = getLocalRotation().getEuler();
	angle = { tnl::ToDegree(angle.x), tnl::ToDegree(angle.y), tnl::ToDegree(angle.z) };
	//angle = { abs(angle.x), abs(angle.y), abs(angle.z) }; double q0q0 = q0 * q0;
	double q0 = getRotation().x;
	double q1 = getRotation().y;
	double q2 = getRotation().z;
	double q3 = getRotation().w;
	double q0q0 = q0 * q0;
	double q0q1 = q0 * q1;
	double q0q2 = q0 * q2;
	double q0q3 = q0 * q3;
	double q1q1 = q1 * q1;
	double q1q2 = q1 * q2;
	double q1q3 = q1 * q3;
	double q2q2 = q2 * q2;
	double q2q3 = q2 * q3;
	double q3q3 = q3 * q3;
	float z = atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3);
	float x = asin(2.0 * (q0q2 - q1q3));
	float y = atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3);
	//return angle;
	return { -z, y, x };
}
void ike::Transform::setLocalEulerAngle(const tnl::Vector3 angle) {
	if (getLocalEulerAngle() == angle) { return; }

	setLocalRotation(eulerToQuaternion(angle));
}

tnl::Quaternion ike::Transform::eulerToQuaternion(tnl::Vector3 euler) {
	tnl::Quaternion rot = tnl::Quaternion::RotationAxis(tnl::Vector3::front, tnl::ToRadian(euler.z));
	rot *= tnl::Quaternion::RotationAxis(tnl::Vector3::up, tnl::ToRadian(euler.y));
	rot *= tnl::Quaternion::RotationAxis(tnl::Vector3::right, tnl::ToRadian(euler.x));
	float x = euler.x / 2;
	float y = euler.y / 2;
	float z = euler.z / 2;
	DirectX::XMFLOAT4 fx4 = DirectX::XMFLOAT4(
		(cos(x) * cos(y) * cos(z) - sin(x) * sin(y) * sin(z)),
		(sin(x) * cos(y) * cos(z) - cos(x) * sin(y) * sin(z)),
		(cos(x) * sin(y) * cos(z) - sin(x) * cos(y) * sin(z)),
		(cos(x) * cos(y) * sin(z) - sin(x) * sin(y) * cos(z)));
	rot = tnl::Quaternion(fx4);

	return rot;
}

#endif


//--------------------スケール関連--------------------------------------


tnl::Vector3 ike::Transform::getScale() const {
	this;
	if (getParent() != nullptr) {
		return getParent()->toWarldScale(getLocalScale());
	}
	else {
		return getLocalScale();
	}
}
void ike::Transform::setScale(const tnl::Vector3& scale) {
	if (getParent() != nullptr) {
		setLocalScale(getParent()->toLocalScale(scale));
	}
	else {
		setLocalScale(scale);
	}
}

tnl::Vector3 ike::Transform::getLocalScale() const {
	return localScale_;
}
void ike::Transform::setLocalScale(const tnl::Vector3& scale) {
	localScale_ = scale;
}




//------------------親子関連--------------------------------------------


bool ike::Transform::setParent(Transform* parent) {
	if (parent != nullptr) {
		setLocalPosition(parent->toLocalPosition(getPosition()));
		setLocalScale(parent->toLocalScale(getScale()));
		setLocalRotation(parent->toLocalRotation(getRotation()));
		return tree_->setParent(parent->tree_);
	}
	else {
		setLocalPosition(getPosition());
		setLocalScale(getScale());
		setLocalRotation(getRotation());
		return tree_->setParent(nullptr);
	}
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




//------------------オブジェクトの軸-----------------------------


tnl::Vector3 ike::Transform::up() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::up, getRotation());
}
tnl::Vector3 ike::Transform::right() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::right, getRotation());
}
tnl::Vector3 ike::Transform::front() const {
	return tnl::Vector3::TransformCoord(tnl::Vector3::front, getRotation());
}




//-------------------移動関数---------------------------------------


void ike::Transform::move(const tnl::Vector3& value) {
	if (value.length() == 0) {
		return;
	}
	setPosition(getPosition() + value);
}

void ike::Transform::ownMove(const tnl::Vector3& value) {
	if (value.length() == 0) {
		return;
	}
	//tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	move(axis);
}



//------------------回転関数-------------------------------

#if ROTATE
void ike::Transform::eulerRotate(const tnl::Vector3& value) {
	if (value.length() == 0) {
		return;
	}
	setRotation(getRotation() * tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(value), value.length() / 180 * tnl::PI));
}
void ike::Transform::ownEulerRotate(const tnl::Vector3& value) {
	if (value.length() == 0) {
		return;
	}
	tnl::Vector3 vec = tnl::Vector3::TransformCoord(value, getLocalRotation());
	setLocalRotation(getLocalRotation() * tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(vec), vec.length() / 180 * tnl::PI));
}
#endif


//-----------------座標系変換-------------------------------------------------

#if CONVERT
tnl::Vector3 ike::Transform::toWarldPosition(const tnl::Vector3& position) const {
	tnl::Vector3 scale = getScale();
	tnl::Vector3 right = this->right() * (position.x * scale.x);
	tnl::Vector3 up = this->up() * (position.y * scale.y);
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
tnl::Quaternion ike::Transform::toWorldRotation(const tnl::Quaternion& rotation) const noexcept {
	return getRotation() * rotation;
}
tnl::Quaternion ike::Transform::toLocalRotation(const tnl::Quaternion& rotation) const noexcept {
	return tnl::Quaternion::Subtract(getRotation(), rotation);
}
#endif