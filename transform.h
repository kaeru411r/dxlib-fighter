#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include <list>
#include "tree.h"

namespace ike {
	class Transform : public ike::Tree {

	public:
		Transform();
		~Transform();


		tnl::Vector3 getPosition() const;
		void setPosition(const tnl::Vector3 position);
		tnl::Quaternion getRotation() const;
		void setRotation(const tnl::Quaternion rotation);



		tnl::Vector3 up() const;
		tnl::Vector3 left() const;
		tnl::Vector3 front() const;

		void localRotate(const tnl::Vector3 value);
		void localMove(const tnl::Vector3 value);

		void Rotate(const tnl::Vector3 value);
		void Move(const tnl::Vector3 value);

	private:

		tnl::Quaternion rotation_;
		tnl::Vector3 position_;

		void followRotate(const tnl::Vector3 value);
		void followMove(const tnl::Vector3 value);

	};
}