#ifndef NUCLEARMISSILEBULLET_HPP_INCLUDED
#define NUCLEARMISSILEBULLET_HPP_INCLUDED

#include <allegro5/base.h>
#include <list>

#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class NuclearMissileBullet : public Bullet {
protected:
	const float rotateRadian = 2 * ALLEGRO_PI;
	std::list<Bullet*>::iterator lockedBulletIterator;
public:
	explicit NuclearMissileBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void Update(float deltaTime) override;
	void OnExplode(Enemy* enemy) override;



};
#endif // NUCLEARMISSILEBULLET_HPP_INCLUDED
