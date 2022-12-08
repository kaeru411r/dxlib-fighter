#pragma once
#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "transform.h"
#include "tree.h"
#include "renderObject.h"

dxe::Camera* camera = nullptr;
dxe::Mesh* mesh = nullptr;
dxe::Mesh* mesh2 = nullptr;
dxe::Mesh* mesh3 = nullptr;
ike::RenderObject* ob = nullptr;
ike::RenderObject* ob2 = nullptr;
ike::RenderObject* ob3 = nullptr;
float size = 1;

bool init = false;
void gameMain(float delta_time) {
	if (!init) {
		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
		camera->pos_ = { 100, 100, 500 };
		mesh = dxe::Mesh::CreateBoxMV(50);
		mesh->setTexture(dxe::Texture::CreateFromFile("graphics/box.bmp"));
		mesh->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob = new ike::RenderObject(mesh);
		mesh2 = mesh->createClone();
		mesh2->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob2 = new ike::RenderObject(mesh2);
		mesh3 = mesh->createClone();
		mesh3->flg_dbg_line_ = dxe::Mesh::fDebugLine::FLG_AXIS;
		ob3 = new ike::RenderObject(mesh3);
		//ike::Tree* t = tr_;
		ob2->getTransform()->setParent(ob->getTransform());
		ob3->getTransform()->setParent(ob2->getTransform());
		ob->getTransform()->setParent(ob3->getTransform());
		ob2->getTransform()->setPosition({ -50, 0, 0 });
		ob3->getTransform()->setLocalPosition({ -50, 0, 0 });
		//ob->getTransform()->setLocalScale({ 2, 2, 2 });
		ob2->getTransform()->setScale({ 0.5f, 0.5f, 0.5f });
		


		init = true;
	}

	clsDx();
	printfDx("ヨー　    　Q,E\n");
	printfDx("ロール　    A,D\n");
	printfDx("ピッチ　    W,S\n");
	printfDx("拡大、縮小　↑,↓\n");
	tnl::Vector3 position = ob->getTransform()->toWarldPosition(ob->getTransform()->toLocalPosition({0, 0, 0}));
	tnl::Vector3 position3 = ob->getTransform()->toLocalPosition({0, 0, 0});
	tnl::Vector3 position2 = ob->getTransform()->getPosition();
	printfDx("%f %f %f\n", position.x, position.y, position.z);
	printfDx("%f %f %f\n", position3.x, position3.y, position3.z);
	printfDx("%f %f %f\n", position2.x, position2.y, position2.z);


	tnl::Vector3 vec;
	//ロール
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		vec += tnl::Vector3::front * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		vec += -tnl::Vector3::front * 2;
	}
	//ピッチ
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		vec += -tnl::Vector3::right * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		vec += tnl::Vector3::right * 2;
	}
	//ヨー
	if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		vec += -tnl::Vector3::up * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		vec += tnl::Vector3::up * 2;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) {
		size *= 1.01f;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) {
		size *= 0.99f;
	}
	ob->getTransform()->ownEulerRotate(vec);
	//ob2->getTransform()->ownEulerRotate(tnl::Vector3::right * 10);
	//ob3->getTransform()->ownEulerRotate(tnl::Vector3::right * 10);
	ob->getTransform()->ownMove(tnl::Vector3::left * size);
	ob->getTransform()->setScale({ size, size , size });
	camera->update();

	ob->render(camera);
	ob2->render(camera);
	ob3->render(camera);

	DrawGridGround(camera, 50, 20);
}

