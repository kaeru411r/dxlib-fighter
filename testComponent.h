#pragma once
#include "component.h"

namespace ike {
	class testComponent : public ike::Component {

	public:
		~testComponent();

		bool update(const float deltaTime);
	};
}