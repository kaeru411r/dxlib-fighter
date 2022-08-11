#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "transform.h"
#include "meshTransform.h"

namespace ike {
	class Object {

	public:

		Object(dxe::Mesh* mesh);
		~Object();
		ike::MeshTransform* transform;


	private:
	};
}