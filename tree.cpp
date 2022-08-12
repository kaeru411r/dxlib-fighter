#include "tree.h"


ike::Tree::Tree() {
}
ike::Tree::~Tree() {
	setParent(nullptr);
	removeAllChildren();
}

void ike::Tree::setParent(Tree* data) {
	std::string a = typeid(*this).name();
	if (parent_ == data) {
		return;
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
}
void ike::Tree::removeAllChildren() {
	auto it = children_.begin();
	while (!children_.empty() || it != children_.end()) {
		std::list<Tree*>::iterator buf = it;
		if (!children_.empty()) {
			buf++;
		}
		(*it)->setParent(nullptr);
		it = buf;
	}
	children_.clear();

}
bool ike::Tree::childrenContains(const Tree* data) {
	if (data == nullptr) {
		return false;
	}
	std::list<Tree*>::iterator it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			return true;
		}
		it++;
	}
	return false;

}

bool ike::Tree::allChildrenContains(const Tree* data) {
	if (data == nullptr) {
		return false;
	}
	std::list<Tree*>::iterator it = children_.begin();
	while (it != children_.end()) {
		if ((*it) == data) {
			return true;
		}
		else if((*it)->allChildrenContains(data)) {
			return true;
		}
		it++;
	}
	return false;
}


ike::Tree* ike::Tree::getParent() const {
	return parent_;

}
std::list<ike::Tree* > ike::Tree::getChildren() const {
	return children_;
}

void ike::Tree::addChild(Tree* data) {
	if (data == nullptr) {
		return;
	}
	if (!childrenContains(data)) {
		children_.emplace_back(data);
	}

}
void ike::Tree::removeChild(Tree* data) {
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
