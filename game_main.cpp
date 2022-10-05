#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "transform.h"
#include "object .h"
#include "tree.h"
#include "renderObject.h"

dxe::Camera* camera = nullptr;
dxe::Mesh* mesh = nullptr;
dxe::Mesh* mesh2 = nullptr;
dxe::Mesh* mesh3 = nullptr;
ike::RenderObject* ob_ = nullptr;
ike::RenderObject* ob2_ = nullptr;
ike::RenderObject* ob3_ = nullptr;

bool init = false;
void gameMain(float delta_time) {
	if (!init) {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		camera->pos_ = { 100, 100, -300 };
		mesh = dxe::Mesh::CreateBoxMV(50);
		mesh->setTexture("graphics/box.bmp");
		mesh->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob_ = new ike::RenderObject(mesh);
		mesh2 = dxe::Mesh::CreateBoxMV(50);
		mesh2->setTexture("graphics/box.bmp");
		mesh2->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob2_ = new ike::RenderObject(mesh2);
		mesh3 = dxe::Mesh::CreateBoxMV(50);
		mesh3->setTexture("graphics/box.bmp");
		mesh3->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob3_ = new ike::RenderObject(mesh3);
		//ike::Tree* t = tr_;
		ob2_->getTransform()->setParent(ob_->getTransform());
		ob3_->getTransform()->setParent(ob2_->getTransform());
		ob_->getTransform()->setParent(ob3_->getTransform());
		ob2_->getTransform()->setPosition({ -50, 0, 0 });
		ob3_->getTransform()->setLocalPosition({ -50, 0, 0 });
		//ob_->getTransform()->setRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, 3.141592f));
		//ob2_->getTransform()->setLocalPosition({ 50, 0, 0 });
		ob_->getTransform()->setLoaclEulerAngle({ 3.141892 / 2, 0, 0 });
		//ob2_->getTransform()->setLoaclEulerAngle({ -3.141592 / 2, 3.141592, 3.141592 / 2 });
		//ob2_->getTransform()->setLoaclEulerAngle({ 0, 3.141592, 0 });
		ob_->getTransform()->setLocalScale({ 2, 2, 2});
		auto v = ob_->getTransform()->getEulerAngle();
		auto v2 = ob2_->getTransform()->getEulerAngle();

		init = true;
	}

	ob_->getTransform()->move({ 0, 0, 1 });

	tnl::Vector3 vec = { 0,0,0 };
	//ロール
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		vec += tnl::Vector3::front * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		vec += -tnl::Vector3::front * 2;
	}
	//ピッチ
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		vec += -tnl::Vector3::left * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		vec += tnl::Vector3::left * 2;
	}
	//ヨー
	if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		vec += -tnl::Vector3::up * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		vec += tnl::Vector3::up * 2;
	}
	ob_->getTransform()->ownMove(tnl::Vector3::front);
	//ob_->getTransform()->setScale(ob_->getTransform()->getScale() * 1.01);
	//ob2_->getTransform()->eulerRotate({ 0.000001, 0, 0 });

	//clsDx();
	//ob3_->getTransform()->ownEulerRotate(vec /180 * 3.151892);
	//printfDx("%f, %f, %f\n", ob_->getTransform()->getScale().x, ob_->getTransform()->getScale().y, ob_->getTransform()->getScale().z);
	//printfDx("%f, %f, %f\n", ob2_->getTransform()->getPosition().x, ob2_->getTransform()->getPosition().y, ob2_->getTransform()->getPosition().z);
	ob_->getTransform()->getPosition();
	//ob_->getTransform()->getRotation();
	ob_->getTransform()->getEulerAngle();
	ob_->getTransform()->getScale();

	camera->update();

	ob_->render(camera);
	ob2_->render(camera);
	ob3_->render(camera);

	DrawGridGround(50, 20);
}

