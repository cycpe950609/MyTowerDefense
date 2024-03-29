#include <cmath>
#include <random>
#include <string>
#include <utility>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "NuclearMissileBullet.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "ExplosionEffect.hpp"
#include <iostream>
#include "Point.hpp"
class Turret;

NuclearMissileBullet::NuclearMissileBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-4.png", 150, 4, position, forwardDirection, rotation + ALLEGRO_PI / 2, parent) {
}
void NuclearMissileBullet::Update(float deltaTime) {
	if (!Target) {
		float minDistance = INFINITY;
		Enemy* enemy = nullptr;
		for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
			Enemy* e = dynamic_cast<Enemy*>(it);
			float distance = (e->Position - Position).Magnitude();
			if (distance < minDistance) {
				minDistance = distance;
				enemy = e;
			}
		}
		if (!enemy) {
			Bullet::Update(deltaTime);
			return;
		}
		Target = enemy;
		Target->lockedBullets.push_back(this);
		lockedBulletIterator = std::prev(Target->lockedBullets.end());
	}
	Engine::Point originVelocity = Velocity.Normalize();
	Engine::Point targetVelocity = (Target->Position - Position).Normalize();
	float maxRotateRadian = rotateRadian * deltaTime;
	float cosTheta = originVelocity.Dot(targetVelocity);
	// Might have floating-point precision error.
	if (cosTheta > 1) cosTheta = 1;
	else if (cosTheta < -1) cosTheta = -1;
	float radian = acos(cosTheta);
	if (abs(radian) <= maxRotateRadian)
		Velocity = targetVelocity;
	else
		Velocity = ((abs(radian) - maxRotateRadian) * originVelocity + maxRotateRadian * targetVelocity) / radian;
	Velocity = speed * Velocity.Normalize();
	Rotation = atan2(Velocity.y, Velocity.x) + ALLEGRO_PI / 2;
	Bullet::Update(deltaTime);
}
void NuclearMissileBullet::OnExplode(Enemy* enemy) {
	Target->lockedBullets.erase(lockedBulletIterator);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4, 10);

	for(auto it : getPlayScene()->EnemyGroup->GetObjects())
	{
	     if(it == enemy)
	     {
		  continue;
	     }
	     if((it->Position - this->Position).Magnitude() < 150.0)
	     {
		  ((Enemy*)it)->Hit(this->damage/2);
		  //getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(((Enemy*)it)->Position.x, ((Enemy*)it)->Position.y,"purple"));
	     }
	}
	/*
	for(int t = 0;t < 20;t++)
	{
	    getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x + 5*t*cos(t*ALLEGRO_PI/5), Position.y + 5*t*sin(t*ALLEGRO_PI/5),"purple")); 
	}*/
	
	for(int i = 0;i < 150;i = i + 50)
	    for(double j = 0.0;j < 2*ALLEGRO_PI;j = j + ALLEGRO_PI/8)
	    {
		getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x + i*cos(j), Position.y + i * sin(j),"purple"));
		//Engine::Point p = Engine::Point(Position.x + i,Position.y + j);
		//if((p - Position).Magnitude() < 150)
		//   getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(p.x, p.y,"purple"));
	    }
	
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y,"purple"));
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-3.png", dist(rng), enemy->Position.x, enemy->Position.y));
}
