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
		Transform(dxe::Mesh* mesh);
		Transform(const std::list<dxe::Mesh*> meshes);
		template<typename... tMeshes>
		Transform(tMeshes... meshes) {
			dxe::Mesh* ms[] = { static_cast<dxe::Mesh*>(meshes)... };
			for (dxe::Mesh* m : ms) {
				meshes_.push_back(m);
			}
		}
		~Transform();


		tnl::Vector3 getPosition() const;
		void setPosition(const tnl::Vector3 position);
		tnl::Vector3 getLocalPosition() const;
		void setLocalPosition(const tnl::Vector3 position);
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
		virtual void ownMove(const tnl::Vector3 value);

		//virtual void localEulerRotate(const tnl::Vector3 value);
		//virtual void localMove(const tnl::Vector3 value);

		virtual void eulerRotate(const tnl::Vector3 value);
	 	virtual void move(const tnl::Vector3 value);

	private:

		tnl::Quaternion rotation_;
		tnl::Vector3 position_;
		tnl::Vector3 scale_ = {1, 1, 1};

		std::list<dxe::Mesh*> meshes_;

		void followRotate(const tnl::Vector3 value);
		void followMove(const tnl::Vector3 value);
		void followScale(const tnl::Vector3 value);

	};
}