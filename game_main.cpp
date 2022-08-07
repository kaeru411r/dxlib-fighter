#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "transform.h"
#include "object .h"
#include "tree.h"

dxe::Camera* camera = nullptr;
dxe::Mesh* mesh = nullptr;
ike::Object* ob_ = nullptr;

bool init = false;

void gameMain(float delta_time) {
	if (!init) {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		camera->pos_ = { 100, 100, -300 };
		mesh = dxe::Mesh::CreateBoxMV(50);
		mesh->setTexture("graphics/box.bmp");
		mesh->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ike::Transform* tr_ = new ike::Transform; 
		ob_ = new ike::Object(mesh);
		ike::Tree* t = tr_;
		auto a = typeid(t).before(typeid(tr_));/*
		auto b = typeid(*t).before();
		auto c = typeid(tr_).before();
		auto d = typeid(*tr_).before();*/
		//a = "string";
		tr_->setParent(t);
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

	ob_->transform->localRotate(vec);

	camera->update();

	mesh->render(camera);

	DrawGridGround(50, 20);
}

