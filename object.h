#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "meshTransform.h"
#include "iUpdate.h"

namespace ike {
	class Object : ike::IUpdate{

	public:

		Object();
		~Object();

		virtual bool update(const float deltaTime) { return true; }

		virtual bool fixedUpdate(const float fixedDeltaTime) { return true; }

	private:
	};
}