#pragma once
#include<list>
#include<memory>
#include "../dxlib_ext/dxlib_ext.h"

namespace ike {

	template <typename T>
	class Tree : public std::enable_shared_from_this<Tree<T>> {

	public:
		Tree(std::shared_ptr<T> data) {
//			data_ = std::shared_ptr<T>(data);
			data_ = data;
		}

		Tree(){}

		virtual ~Tree() {}

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

		std::list<std::shared_ptr<Tree<T>>> getChildren() const {
			return children_;
		}


		bool setParent(std::shared_ptr<Tree<T>> data) {
			if (parent_ == data) {
				return false;
			}
			if (allChildrenContains(data)) {
				while (ErrorLogFmtAdd("Error : 渡されたオブジェクトはこのオブジェクトの子オブジェクトです") != -1) {}
				return false;
			}
			if (parent_ != nullptr) {
				parent_->removeChild(this->shared_from_this());
			}
			//parent_ = std::make_shared<ike::Tree<std::shared_ptr<T>>>(data);
			parent_ = data;
			if (data != nullptr) {
				if (!childrenContains(data)) {
					data->addChild(this->shared_from_this());
				}
			}
			return true;
		}

		std::shared_ptr<Tree<T>> getParent() const {
			return parent_;
		}

		bool childrenContains(const std::shared_ptr<T> data) {
			if (data == nullptr) {
				return false;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((*it)->getData() == data) {
					return true;
				}
				it++;
			}
			return false;

		}
		bool allChildrenContains(const std::shared_ptr<T> data) {
			if (data == nullptr) {
				return false;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((*it)->getData() == data) {
					return true;
				}
				else if ((*it)->allChildrenContains(data)) {
					return true;
				}
				it++;
			}
			return false;
		}

		std::shared_ptr<T> getData() {
			return data_;
		}

	private:

		void addChild(std::shared_ptr<Tree<T>> data) {
			if (data == nullptr) {
				return;
			}
			if (!childrenContains(data)) {
				children_.emplace_back(data);
			}

		}
		void removeChild(std::shared_ptr<Tree<T>> data) {
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

	private:


		std::shared_ptr<T> data_ = nullptr;


		std::shared_ptr<Tree<T>> parent_ = nullptr;
		std::list<std::shared_ptr<Tree<T>>> children_;
	};
}