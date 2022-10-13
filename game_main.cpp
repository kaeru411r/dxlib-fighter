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
tnl::Vector3 vec_;

bool init = false;
void gameMain(float delta_time) {
	if (!init) {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		camera->pos_ = { 100, 100, 500 };
		mesh = dxe::Mesh::CreateBoxMV(50);
		mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
		mesh->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob_ = new ike::RenderObject(mesh);
		mesh2 = dxe::Mesh::CreateBoxMV(50);
		mesh2->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
		mesh2->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob2_ = new ike::RenderObject(mesh2);
		mesh3 = dxe::Mesh::CreateBoxMV(50);
		mesh3->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
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
		//ob_->getTransform()->setLocalEulerAngle({ tnl::PI / 2, 0, 0 });
		//ob2_->getTransform()->setLocalEulerAngle({ -3.141592 / 2, 3.141592, 3.141592 / 2 });
		//ob2_->getTransform()->setLocalEulerAngle({ 0, 3.141592, 0 });
		//ob_->getTransform()->eulerRotate({ 0, tnl::ToRadian(45), 0 });
		//ob_->getTransform()->setLocalEulerAngle({ 0, -90, 0 });
		//ob_->getTransform()->eulerRotate({ 0, 90, 00 });
		//ob_->getTransform()->eulerRotate({ 0, 0, 45 });
		//ob_->getTransform()->ownEulerRotate({ 0, 0, 100 });
		//ob_->getTransform()->ownEulerRotate({ 0, 0, 10 });
		//ob_->getTransform()->setEulerAngle({ 0, 45, -45 });
		//printfDx("%f\n", ob_->getTransform()->getEulerAngle().z);
		ob_->getTransform()->setLocalScale({ 2, 2, 2 });
		ob2_->getTransform()->setScale({ 1, 1, 1 });

		init = true;
		//ob_->getTransform()->setEulerAngle({ tnl::ToRadian( 90), 0, 0 });
		vec_ = ob_->getTransform()->getLocalEulerAngle();
		vec_ = ob_->getTransform()->getLocalEulerAngle();
	}

	clsDx();
	//ob_->getTransform()->move({ 0, 0, 1 });

	
	//ロール
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		vec_ += tnl::Vector3::front * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		vec_ += -tnl::Vector3::front * 2;
	}
	//ピッチ
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		vec_ += -tnl::Vector3::left * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		vec_ += tnl::Vector3::left * 2;
	}
	//ヨー
	if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		vec_ += -tnl::Vector3::up * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		vec_ += tnl::Vector3::up * 2;
	}
	//ob_->getTransform()->ownMove(tnl::Vector3::front);
	//ob_->getTransform()->setScale(ob_->getTransform()->getScale() * 1.01);
	//ob2_->getTransform()->eulerRotate({ 0.000001, 0, 0 });

	ob_->getTransform()->setLocalEulerAngle(vec_);

	printfDx("%f, %f, %f\n", vec_.x / 180 * tnl::PI, vec_.y / 180 * tnl::PI, vec_.z / 180 * tnl::PI);
	printfDx("%f, %f, %f\n\n", vec_.x, vec_.y, vec_.z);
	printfDx("%f, %f, %f\n", ob_->getTransform()->getEulerAngle().x, ob_->getTransform()->getEulerAngle().y, ob_->getTransform()->getEulerAngle().z);
	tnl::Vector3 angle = ob_->getTransform()->getRotation().getEuler();
	printfDx("%f, %f, %f\n", angle.x, angle.y, angle.z);
	printfDx("%f, %f, %f\n\n", ob_->getTransform()->getEulerAngle().x / angle.x, ob_->getTransform()->getEulerAngle().y / angle.y, ob_->getTransform()->getEulerAngle().z / angle.z);
	//ob_->getTransform()->setEulerAngle(vec_);
	printfDx("%f, %f, %f\n", ob_->getTransform()->getEulerAngle().x, ob_->getTransform()->getEulerAngle().y, ob_->getTransform()->getEulerAngle().z);
	angle = ob_->getTransform()->getRotation().getEuler();
	printfDx("%f, %f, %f\n", angle.x, angle.y, angle.z);
	printfDx("%f, %f, %f\n", ob_->getTransform()->getEulerAngle().x / angle.x, ob_->getTransform()->getEulerAngle().y / angle.y, ob_->getTransform()->getEulerAngle().z / angle.z);
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

	DrawGridGround(camera, 50, 20);
}

