#pragma once
#include "object.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "meshTransform.h"

//class dxe::Camera;
namespace ike {

	class RenderObject : public Object {
	public:

		RenderObject(dxe::Mesh* mesh);
		~RenderObject();



	private:
		
		
	};




}