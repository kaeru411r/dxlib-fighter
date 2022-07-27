#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include <list>

namespace ike {
	class Transform {

	public:
		Transform(dxe::Mesh* mesh);
		~Transform();


		dxe::Mesh* mesh_ = nullptr;

		tnl::Vector3 getPosition() const;
		void setPosition(const tnl::Vector3 position);
		tnl::Quaternion getRotation() const;
		void setRotation(const tnl::Quaternion rotation);


		void setParent(Transform* data);
		void removeAllChildren();
		bool childrenContains(const Transform* data);

		tnl::Vector3 up() const;
		tnl::Vector3 left() const;
		tnl::Vector3 front() const;

		void localRotate(const tnl::Vector3 value);
		void localMove(const tnl::Vector3 value);

		void Rotate(const tnl::Vector3 value);
		void Move(const tnl::Vector3 value);

	private:

		Transform* parent_ = nullptr;
		std::list<ike::Transform*> children_;

		void addChild(Transform* data);
		void removeChild(Transform* data);

	};
}