#pragma once
#include "component.h"

namespace ike {
	class testComponent : public ike::Component {

	public:

		bool update(const float deltaTime);
	};
}