#pragma once
#include "Framework/Actor.h"

class PointMultiplyer : public kiko::Actor
{
public:
	PointMultiplyer(float speed, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		lifespan = 4.0f;
	}

	void Update(float dt) override;
	void OnCollissionEnter(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;
};