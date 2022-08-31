#include "object .h"

class dxe::Camera;
namespace ike {

	class RenderObject : public Object {
	public:

		RenderObject(dxe::Mesh* mesh);
		~RenderObject();

		Transform* getTransform() const;

		void update(float deltaTime);

		void render(const dxe::Camera* camera);

	private:

		ike::MeshTransform* transform_;
		
	};




}