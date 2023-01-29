#pragma once
#include "transform.h"
#include "../dxlib_ext/dxlib_ext.h"

class Transfrom;
class Camera;
namespace ike {


	class MeshTransform : public ike::Transform {

	public:

		//MeshTransform(dxe::Mesh* mesh);

		void constructor(std::any value) override;


		void render(const dxe::Camera* camera);

		

	protected:

		MeshTransform() {};


	private:
		dxe::Mesh* mesh_ = nullptr;

	};
}