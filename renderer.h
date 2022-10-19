#pragma once
#include "component.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "meshTransform.h"

namespace ike {

	class Renderer : public ike::Component {
	public:

		Renderer(dxe::Mesh* mesh);
		~Renderer();

		Transform* getTransform() const;

		bool update(const float deltaTime) {};
		void render(const dxe::Camera* camera);


	private:


		ike::MeshTransform* transform_;

	};
}