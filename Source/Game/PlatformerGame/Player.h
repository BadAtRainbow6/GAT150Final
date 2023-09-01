#pragma once
#include "Framework/Actor.h"


namespace kiko {
	class Player : public kiko::Actor
	{
	public:

		CLASS_DECLARATION(Player)

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollissionEnter(Actor* other) override;
		void OnCollissionExit(Actor* other) override;



	private:
		float speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundCount = 0;

		int m_health = 100;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteComponent = nullptr;
	};
}