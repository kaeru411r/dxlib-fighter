#pragma once
#include "testComponent.h"
#include "../dxlib_ext/dxlib_ext.h"

bool ike::testComponent::update(const float deltaTime) {
	printfDx("update");

	return true;
}