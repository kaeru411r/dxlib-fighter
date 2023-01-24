#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "scene.h"

namespace ike {

	class gameEngineManager {
	public:
		static std::shared_ptr<ike::gameEngineManager> getInstance();
		static void destroy();

		void update(const float& deltaTime);

	private:
		gameEngineManager();
		static std::shared_ptr<gameEngineManager> instance;

		std::list<std::shared_ptr<Scene>> scenes;
	};

}