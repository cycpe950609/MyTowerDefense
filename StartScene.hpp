#ifndef STARTSCENE_HPP_INCLUDED
#define STARTSCENE_HPP_INCLUDED

#include "IScene.hpp"

class StartScene final : public Engine::IScene {
private:
public:
	explicit StartScene() = default;
	void Initialize() override;
	//void Update(float deltaTime) override;
	void ButtonOnClick(int btnID);
};



#endif // STARTSCENE_HPP_INCLUDED
