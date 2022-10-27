#include "transform.h"

//using namespace ike;

ike::Transform::Transform() {
	localPosition_ = { 0, 0, 0 };
	localRotation_ = tnl::Quaternion();
	localScale_ = { 1, 1, 1 };
}
ike::Transform::~Transform() {
	setParent(nullptr);
	removeAllChildren();
}



//-----------ポジション関連-----------------------

		/// <summary>現在のPositionを返す</summary>
		/// <returns></returns>
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
		setLocalPosition({ right, up, front });
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




//------------------親子関連--------------------------------------------


bool ike::Transform::setParent(Transform* parent) {
	tnl::Vector3 pos = -parent->getPosition();
	//tnl::Vector3 rot = -parent->localRotation_.getEuler();
	if (getParent() != nullptr) {
		pos += getParent()->getPosition();
		//rot += getParent()->localRotation_.getEuler();
	}
	localPosition_ += pos;
	//localRotation_ *= 
	return ike::Transform::setParent(parent);
}

ike::Transform* ike::Transform::getParent() const {
	return dynamic_cast<Transform*>(ike::Transform::getParent());
}
std::list<ike::Transform*> ike::Transform::getChildren() const {
	std::list<ike::Transform*> list;
	for (ike::Transform* t : ike::Transform::getChildren()) {
		list.push_back(dynamic_cast<ike::Transform*>(t));
	}
	return list;
}

bool ike::Transform::childrenContains(const Transform* data) {
	return ike::Transform::childrenContains(data);
}
bool ike::Transform::allChildrenContains(const Transform* data) {
	return ike::Transform::allChildrenContains(data);
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
	//tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	tnl::Vector3 axis = tnl::Vector3::TransformCoord(value, getRotation());
	move(axis);
}



//------------------回転関数-------------------------------

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
	setLocalRotation(getLocalRotation()* tnl::Quaternion::RotationAxis(tnl::Vector3::Normalize(vec), vec.length() / 180 * tnl::PI));
	//tnl::Vector3 axis = { tnl::ToRadian(value.x), tnl::ToRadian(value.y), tnl::ToRadian(value.z) };
	//tnl::Vector3 axis = tnl::Vector3::TransformCoord(tnl::Vector3::Normalize(value), getRotation())/* * value.length()*/;
	//tnl::Vector3 axis = getEulerAngle() + value;
	//axis = { axis.x * value.x, axis.y * value.y , axis.z * value.z };
	//eulerRotate(axis /** tnl::ToRadian(value.length())*/);
}
#endif
bool ike::Transform::setParent(Transform* data) {
	std::string a = typeid(*this).name();
	if (parent_ == data) {
		return false;
	}
	if (allChildrenContains(data)) {
		while (ErrorLogFmtAdd("Error : 渡されたオブジェクトはこのオブジェクトの子オブジェクトです") != -1) {}
		return false;
	}
	if (parent_ != nullptr) {
		parent_->removeChild(this);
	}
	parent_ = data;
	if (data != nullptr) {
		if (!childrenContains(data)) {
			data->addChild(this);
		}
	}
	return true;
}
void ike::Transform::removeAllChildren() {
	auto it = children_.begin();
	while (!children_.empty() || it != children_.end()) {
		std::list<Transform*>::iterator buf = it;
		if (!children_.empty()) {
			buf++;
		}
		(*it)->setParent(nullptr);
		it = buf;
	}
	children_.clear();

}
bool ike::Transform::childrenContains(const Transform* data) {
	if (data == nullptr) {
		return false;
	}
	std::list<Transform*>::iterator it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			return true;
		}
		it++;
	}
	return false;

}

bool ike::Transform::allChildrenContains(const Transform* data) {
	if (data == nullptr) {
		return false;
	}
	std::list<Transform*>::iterator it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			return true;
		}
		else if ((*it)->allChildrenContains(data)) {
			return true;
		}
		it++;
	}
	return false;
}


ike::Transform* ike::Transform::getParent() const {
	return parent_;
}
std::list<ike::Transform* > ike::Transform::getChildren() const {
	return children_;
}

void ike::Transform::addChild(Transform* data) {
	if (data == nullptr) {
		return;
	}
	if (!childrenContains(data)) {
		children_.emplace_back(data);
	}

}
void ike::Transform::removeChild(Transform* data) {
	if (children_.empty()) {
		return;
	}
	auto it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			children_.erase(it);
			break;
		}
		it++;
	}
}
