#pragma once
#include "transform.h"
#include "../dxlib_ext/dxlib_ext.h"

class Transfrom;
class Camera;
namespace ike {

	class MeshTransform : public ike::Transform {

	public:

		MeshTransform(dxe::Mesh* mesh);

		void setPosition(const tnl::Vector3 position);

		void setLocalPosition(const tnl::Vector3 position);
		void setLocalRotation(const tnl::Quaternion rotation);
		void setLocalScale(const tnl::Vector3 scale);

		void render(const dxe::Camera* camera);

		void eulerRotate(const tnl::Vector3 value);

		void ownEulerRotate(const tnl::Vector3 value);

		


	private:
		dxe::Mesh* mesh_ = nullptr;

	};
}