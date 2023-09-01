#pragma once
#include "Framework/Actor.h"



namespace kiko {
class Weapon : public kiko::Actor
{
public:

	CLASS_DECLARATION(Weapon)

	/*
	Weapon() = default;
	Weapon(float speed, const kiko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		lifespan = 2.0f;
	}
	*/

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollissionEnter(Actor* other);
public:
	class PhysicsComponent* m_physicsComponent = nullptr;

	float speed = 0;
	float m_turnRate = 0;
};
}