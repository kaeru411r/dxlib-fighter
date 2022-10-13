#pragma once

namespace ike {

	class Component {

	public:
		Component();
		virtual ~Component();

		virtual bool update(float deltaTime) = 0;


	private:
	};
}