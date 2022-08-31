#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "meshTransform.h"

namespace ike {
	class Object {

	public:

		Object();
		~Object();

		virtual void update(const float deltaTime) = 0;

	private:
	};
}