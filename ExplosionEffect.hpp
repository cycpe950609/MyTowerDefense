#ifndef EXPLOSIONEFFECT_HPP
#define EXPLOSIONEFFECT_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>
#include <string>

#include "Sprite.hpp"

class PlayScene;

class ExplosionEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	ExplosionEffect(float x, float y);
	ExplosionEffect(float x, float y,std::string Color);
	void Update(float deltaTime) override;
private:
	std::string explosion_color = "";
};
#endif // EXPLOSIONEFFECT_HPP
