#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko {
	class Enemey : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Enemey)

		Enemey() = default;
		Enemey(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{
			m_fireTime = 3.0f;
			m_fireTimer = m_fireTime;
		}

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollissionEnter(Actor* other) override;

		bool GetFaceingPlayer() const { return m_faceingPlayer; }
		void SetFaceingPlayer(bool faceingPlayer) { m_faceingPlayer = faceingPlayer; }
	public:
		float speed = 0;
		float turnRate = 0;

		bool m_faceingPlayer = false;

		float m_fireTime = 0;
		float m_fireTimer = 0;

		int m_health = 50;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}