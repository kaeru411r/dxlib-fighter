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
		virtual void setPosition(const tnl::Vector3 position);

		tnl::Vector3 getLocalPosition() const;
		virtual void setLocalPosition(const tnl::Vector3 position);


		tnl::Quaternion getRotation() const;
		void setRotation(const tnl::Quaternion rotation);/*
		tnl::Quaternion getLocalRotation() const;
		void setLocalRotation(const tnl::Quaternion rotation);*/
		tnl::Vector3 getScale() const;
		virtual void setScale(const tnl::Vector3 scale);/*
		tnl::Vector3 getLocalScale() const;
		virtual void setLocalScale(const tnl::Vector3 scale);*/


		bool setParent(Transform* data);

		Transform* getParent() const;
		std::list<Transform*> getChildren() const;

		bool childrenContains(const Transform* data);
		bool allChildrenContains(const Transform* data);



		tnl::Vector3 up() const;
		tnl::Vector3 left() const;
		tnl::Vector3 front() const;

		virtual void ownEulerRotate(const tnl::Vector3 value);
		void ownMove(const tnl::Vector3 value);

		//virtual void localEulerRotate(const tnl::Vector3 value);
		//virtual void localMove(const tnl::Vector3 value);

		virtual void eulerRotate(const tnl::Vector3 value);
	 	void move(const tnl::Vector3 value);

	private:

		tnl::Quaternion rotation_;
		tnl::Vector3 position_;
		tnl::Vector3 scale_ = {1, 1, 1};

		void followRotate(const tnl::Vector3 value);
		void followMove(const tnl::Vector3 value);
		void followScale(const tnl::Vector3 value);

	};
}