#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"


namespace kiko {
	class Enemy : public kiko::Actor
	{
	public:

		CLASS_DECLARATION(Enemy)

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollissionEnter(Actor* other) override;
		void OnCollissionExit(Actor* other) override;



	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		int m_health = 100;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}