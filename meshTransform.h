#pragma once
#include "transform.h"
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"


namespace ike {


	class MeshTransform : public ike::Transform {

	public:

		MeshTransform(dxe::Mesh* mesh);

		void move(const tnl::Vector3 value);
		void eulerRotate(const tnl::Vector3 value);

		void ownMove(const tnl::Vector3 value);
		void ownEulerRotate(const tnl::Vector3 value);

		


	private:
		dxe::Mesh* mesh_ = nullptr;

	};
}