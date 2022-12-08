#pragma once
#include<list>
#include "../dxlib_ext/dxlib_ext.h"

namespace ike {

	template <typename T>
	class Tree {

	public:
		Tree(T* data) {
			data_ = data;
		}

		~Tree() {
		}

		void removeAllChildren() {
			auto it = children_.begin();
			while (!children_.empty() || it != children_.end()) {
				auto buf = it;
				if (!children_.empty()) {
					buf++;
				}
				(*it)->setParent(nullptr);
				it = buf;
			}
			children_.clear();

		}
		
		std::list<Tree<T>*> getChildren() const {
			return children_;
		}


		bool setParent(Tree* data) {
			if (parent_ == data) {
				return false;
			}
			if (allChildrenContains((T*)data)) {
				while (ErrorLogFmtAdd("Error : 渡されたオブジェクトはこのオブジェクトの子オブジェクトです") != -1) {}
				return false;
			}
			if (parent_ != nullptr) {
				parent_->removeChild(this);
			}
			parent_ = data;
			if (data != nullptr) {
				if (!childrenContains((T*)data)) {
					data->addChild(this);
				}
			}
			return true;
		}

		Tree* getParent() const {
			this;
			return parent_;
		}

		bool childrenContains(const T* data) {
			if (data == nullptr) {
				return false;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((T*)(*it) == data) {
					return true;
				}
				it++;
			}
			return false;

		}
		bool allChildrenContains(const T* data) {
			if (data == nullptr) {
				return false;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((T*)(*it) == data) {
					return true;
				}
				else if ((*it)->allChildrenContains(data)) {
					return true;
				}
				it++;
			}
			return false;
		}

		T* getData() {
			return data_;
		}

	private:

		T* data_ = nullptr;


		Tree* parent_ = nullptr;
		std::list<Tree*> children_;

		void addChild(Tree* data) {
			if (data == nullptr) {
				return;
			}
			if (!childrenContains((T*)data)) {
				children_.emplace_back(data);
			}

		}
		void removeChild(Tree* data) {
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
	};
}