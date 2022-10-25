#pragma once
#include "iUpdate.h"

namespace ike {

	class Component : public ike::IUpdate {

	public:
		Component();
		virtual ~Component();

		virtual bool update(const float deltaTime) {};


	private:
	};
}