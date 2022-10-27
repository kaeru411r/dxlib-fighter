#pragma once
#include "object.h"

class dxe::Camera;
namespace ike {

	class RenderObject : public ike::Object {
	public:

		RenderObject(dxe::Mesh* mesh);
		~RenderObject();

		Transform* getTransform() const;

		void render(const dxe::Camera* camera);

	private:

		ike::MeshTransform* transform_;
		
	};




}