#pragma once
#include<list>

namespace ike {

	
	class Tree{

	public:

		void removeAllChildren();

	protected:
		Tree();
		virtual ~Tree();

		bool setParent(Tree* data);

		Tree* getParent() const;
		std::list<Tree*> getChildren() const;

		bool childrenContains(const Tree* data);
		bool allChildrenContains(const Tree* data);


	private:


		Tree* parent_ = nullptr;
		std::list<Tree*> children_;

		void addChild(Tree* data);
		void removeChild(Tree* data);
	};
}