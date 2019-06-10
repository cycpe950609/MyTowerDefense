#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "NuclearMissileBullet.hpp"
#include "NuclearMissileTurrent.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

#include <iostream>

const int NuclearMissileTurret::Price = 1000;
NuclearMissileTurret::NuclearMissileTurret(float x, float y) :
	Turret("play/tower-base.png", "play/turret-4.png", x, y, 1000, Price, 6) {
}
void NuclearMissileTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	//std::cout << diff.x << " " << diff.y << std::endl;
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new NuclearMissileBullet(Position + normalized * 10 - normal * 6, diff, rotation, this));
	//getPlayScene()->BulletGroup->AddNewObject(new NuclearMissileBullet(Position + normalized * 10 + normal * 6, diff, rotation + ALLEGRO_PI/36, this));
	AudioHelper::PlayAudio("missile.wav");
}
