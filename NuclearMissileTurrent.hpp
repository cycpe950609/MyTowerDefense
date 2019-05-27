#ifndef NUCLEARMISSILETURRENT_HPP_INCLUDED
#define NUCLEARMISSILETURRENT_HPP_INCLUDED

#include "Turret.hpp"
class NuclearMissileTurret: public Turret {
public:
	static const int Price;
    NuclearMissileTurret(float x, float y);
    void CreateBullet() override;
};

#endif // NUCLEARMISSILETURRENT_HPP_INCLUDED
