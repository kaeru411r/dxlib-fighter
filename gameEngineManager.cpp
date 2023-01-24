#pragma once
#include "gameEngineManager.h"
std::shared_ptr<ike::gameEngineManager> ike::gameEngineManager::instance;

ike::gameEngineManager::gameEngineManager() {
	scenes.emplace_back(std::make_shared<ike::Scene>());
}

std::shared_ptr<ike::gameEngineManager> ike::gameEngineManager::getInstance() {
	if (instance == nullptr) {
		instance = std::shared_ptr<gameEngineManager>(new gameEngineManager());
	}

	return instance;
}

void ike::gameEngineManager::destroy() {
	instance.reset();
}

void ike::gameEngineManager::update(const float& deltaTime) {
	if (scenes.empty()) {
		return;
	}
	auto it = scenes.begin();
	while (it != scenes.end()) {
		(*it).get()->update(deltaTime);
		it++;
	}
}