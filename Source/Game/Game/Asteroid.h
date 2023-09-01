#pragma once
#include "Framework/Actor.h"

class Asteroid : public kiko::Actor
{
public:
	Asteroid(float speed, float lifespan, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		lifespan = lifespan;
	}

	void Update(float dt) override;
	void OnCollissionEnter(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	int m_health = 70;
};