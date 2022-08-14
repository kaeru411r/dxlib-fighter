#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "transform.h"
#include "object .h"
#include "tree.h"

dxe::Camera* camera = nullptr;
dxe::Mesh* mesh = nullptr;
dxe::Mesh* mesh2 = nullptr;
dxe::Mesh* mesh3 = nullptr;
ike::Object* ob_ = nullptr;
ike::Object* ob2_ = nullptr;
ike::Object* ob3_ = nullptr;

bool init = false;
void gameMain(float delta_time) {
	if (!init) {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		camera->pos_ = { 100, 100, -300 };
		mesh = dxe::Mesh::CreateBoxMV(50);
		mesh->setTexture("graphics/box.bmp");
		mesh->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob_ = new ike::Object(mesh);
		mesh2 = dxe::Mesh::CreateBoxMV(50);
		mesh2->setTexture("graphics/box.bmp");
		mesh2->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob2_ = new ike::Object(mesh2);
		ob2_->transform->move({ 5, 5, 5 });
		mesh3 = dxe::Mesh::CreateBoxMV(50);
		mesh3->setTexture("graphics/box.bmp");
		mesh3->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob3_ = new ike::Object(mesh3);
		ob3_->transform->move({ 10, 10, 10 });
		ike::Transform* tr = ob_->transform;
		tr->ownMove({ 0,0,0 });
		//ike::Tree* t = tr_;
		ob2_->transform->setParent(ob_->transform);
		ob3_->transform->setParent(ob2_->transform);
		if (ob_->transform->allChildrenContains(ob3_->transform)) {
			int a = 0;
		}
		ob_->transform->setParent(ob3_->transform);
		if (ob_->transform->childrenContains(ob2_->transform)) {
			int a = 0;
		}
		auto c = ob_->transform->getChildren();
		ob_->transform->setRotation(tnl::Quaternion::RotationAxis({ 0, 1, 0 }, 3.141592f));

		init = true;
	}
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
	ob_->transform->ownMove(tnl::Vector3::front);
	//ob_->transform->setScale(ob_->transform->getScale() * 1.01);
	ob2_->transform;

	clsDx();
	ob_->transform->ownEulerRotate(vec /180 * 3.151892);
	printfDx("%f, %f, %f, %f\n", ob_->transform->getRotation().x, ob_->transform->getRotation().y, ob_->transform->getRotation().z, ob_->transform->getRotation().w);
	printfDx("%f, %f, %f, %f\n", ob2_->transform->getRotation().x, ob2_->transform->getRotation().y, ob2_->transform->getRotation().z, ob2_->transform->getRotation().w);
	printfDx("%f, %f, %f, %f\n", ob3_->transform->getRotation().x, ob3_->transform->getRotation().y, ob3_->transform->getRotation().z, ob3_->transform->getRotation().w);

	camera->update();

	mesh3->render(camera);
	mesh2->render(camera);
	mesh->render(camera);

	DrawGridGround(50, 20);
}

