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
		tr->localMove({ 0,0,0 });
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
	ob_->transform->localMove(tnl::Vector3::front);
	ob2_->transform;

	ob_->transform->localRotate(vec);

	camera->update();

	mesh3->render(camera);
	mesh2->render(camera);
	mesh->render(camera);

	DrawGridGround(50, 20);
}

