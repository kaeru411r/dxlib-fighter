#pragma once
#include "object.h"

class dxe::Camera;
namespace ike {

	class RenderObject : public ike::Object{
	public:

		RenderObject(dxe::Mesh* mesh);
		~RenderObject();

		std::shared_ptr<ike::MeshTransform> getTransform() const;

		bool render(const dxe::Camera* camera);

	private:

		std::shared_ptr<ike::MeshTransform> transform_;
		
	};




}