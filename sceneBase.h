#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace ike {

	class SceneBase {
	public:
		SceneBase() {};
		virtual ~SceneBase() {};

		virtual void update(const float& deltaTime) = 0;
		virtual void initialize() = 0;
		virtual void start() = 0;
		virtual void end() = 0;

	};
}