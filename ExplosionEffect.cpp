#include <cmath>
#include <string>

#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"
#include <string>

PlayScene* ExplosionEffect::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
ExplosionEffect::ExplosionEffect(float x, float y) : Sprite("play/explosion-orange-1.png", x, y), timeTicks(0),explosion_color("orange") {
	for (int i = 1; i <= 5; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/explosion-" + ExplosionEffect::explosion_color + "-" + std::to_string(i) + ".png"));
	}
}

ExplosionEffect::ExplosionEffect(float x, float y,std::string Color) : Sprite("play/explosion-" + Color + "-1.png", x, y), timeTicks(0),explosion_color(Color) {
	for (int i = 1; i <= 5; i++) {
		bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/explosion-" + ExplosionEffect::explosion_color + "-" + std::to_string(i) + ".png"));
	}
}
void ExplosionEffect::Update(float deltaTime) {
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int phase = floor(timeTicks / timeSpan * bmps.size());
	bmp = bmps[phase];
	Sprite::Update(deltaTime);
}
