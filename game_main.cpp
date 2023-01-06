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
float angle = 45;

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
		//ob->getTransform()->ownEulerRotate({ 45, 75, 60 });
		ob2->getTransform()->setParent(ob->getTransform());
		ob3->getTransform()->setParent(ob2->getTransform());
		ob->getTransform()->setParent(ob3->getTransform());
		ob2->getTransform()->setPosition({ 0, 0, 50 });
		ob3->getTransform()->setLocalPosition({ 0, 0, 50 });
		//ob->getTransform()->setLocalScale({ 2, 2, 2 });
		ob2->getTransform()->setScale({ 0.5f, 0.5f, 0.5f });
		ob3->getTransform()->setScale({ 0.25f, 0.25f , 0.25f });


		init = true;
	}
	ob2->getTransform()->setScale(ob2->getTransform()->getScale());

	tnl::Vector3 vec;
	//ロール
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		vec += tnl::Vector3::right * angle;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S)) {
		vec += tnl::Vector3::left * angle;
	}
	//ピッチ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		vec += tnl::Vector3::front * angle;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		vec += tnl::Vector3::back * angle;
	}
	//ヨー
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {
		vec += tnl::Vector3::down * angle;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)) {
		vec += tnl::Vector3::up * angle;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		size *= 2.0f;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		size *= 0.5f;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		ob->getTransform()->ownMove(tnl::Vector3::front * size * 30);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK)) {
		ob->getTransform()->ownMove(tnl::Vector3::back * size * 30);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P)) {
		ob2->getTransform()->setParent(ob2->getTransform()->getParent() == nullptr ? ob->getTransform() : nullptr);
	}
	ob->getTransform()->ownEulerRotate(vec);
	//ob2->getTransform()->ownEulerRotate(tnl::Vector3::right * 10);
	//ob3->getTransform()->ownEulerRotate(tnl::Vector3::right * 10);
	ob->getTransform()->setScale({ size, size , size });

	clsDx();
	tnl::Vector3 euler = ob->getTransform()->getEulerAngle();
	printfDx("(%f, %f, %f)\n", euler.x, euler.y, euler.z);
	ob->getTransform()->setEulerAngle(euler);
	euler = ob->getTransform()->getEulerAngle();
	printfDx("(%f, %f, %f)\n", euler.x, euler.y, euler.z);
	euler = ob2->getTransform()->getEulerAngle();
	printfDx("(%f, %f, %f)\n", euler.x, euler.y, euler.z);
	euler = ob3->getTransform()->getEulerAngle();
	printfDx("(%f, %f, %f)\n", euler.x, euler.y, euler.z);


	camera->update();

	ob->render(camera);
	ob2->render(camera);
	ob3->render(camera);

	DrawGridGround(camera, 50, 20);
}

