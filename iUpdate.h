#pragma once

namespace ike {

	class IUpdate {

	public:

		IUpdate();
		virtual ~IUpdate();

		virtual bool update(const float deltaTime) = 0;

	private:


	};
}