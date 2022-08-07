#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"

namespace ike {


	class Tree{

	public:
		Tree();
		~Tree();

		void setParent(Tree* data);
		void removeAllChildren();
		bool childrenContains(const Tree* data);


	private:

		Tree* parent_ = nullptr;
		std::list<Tree*> children_;

		void addChild(Tree* data);
		void removeChild(Tree* data);
	};
}