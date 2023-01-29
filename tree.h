#pragma once
#include<list>
#include<memory>
#include"sharedFactory.h"

namespace ike {

	template <typename T>
	class Tree : public ike::SharedFactory<Tree<T>> {

	public:


		//Tree(){}
		void constructor() override {}
		void constructor(std::any value) override {
			data_ = std::any_cast<std::shared_ptr<T>>(value);
		}

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


		bool setParent(std::shared_ptr<Tree<T>> tree) {
			if (parent_ == tree) {
				return false;
			}
			if (allChildrenContains(tree)) {
				while (printf("Error : 渡されたオブジェクトはこのオブジェクトの子オブジェクトです") != -1) {}
				return false;
			}
			if (parent_ != nullptr) {
				parent_->removeChild(this->shared_from_this());
			}
			//parent_ = std::make_shared<ike::Tree<std::shared_ptr<T>>>(tree);
			parent_ = tree;
			if (tree != nullptr) {
				if (!childrenContains(tree)) {
					tree->addChild(this->shared_from_this());
				}
			}
			return true;
		}

		std::shared_ptr<Tree<T>> getParent() const {
			return parent_;
		}

		bool childrenContains(const std::shared_ptr<Tree<T>> tree) {
			if (tree == nullptr) {
				return false;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((*it) == tree) {
					return true;
				}
				it++;
			}
			return false;

		}
		bool allChildrenContains(const std::shared_ptr<Tree<T>> tree) {
			if (tree == nullptr) {
				return false;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((*it) == tree) {
					return true;
				}
				else if ((*it)->allChildrenContains(tree)) {
					return true;
				}
				it++;
			}
			return false;
		}

		std::shared_ptr<T> getData() {
			return data_;
		}



	protected:
	public:
		Tree() {};


	private:

		void addChild(std::shared_ptr<Tree<T>> tree) {
			if (tree == nullptr) {
				return;
			}
			if (!childrenContains(tree)) {
				children_.emplace_back(tree);
			}

		}
		void removeChild(std::shared_ptr<Tree<T>> tree) {
			if (children_.empty()) {
				return;
			}
			auto it = children_.begin();
			while (it != children_.end()) {
				if ((*it) == tree) {
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