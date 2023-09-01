#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Player.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Framework/Components/PhysicsComponent.h"


namespace kiko {
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();



		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		if (m_physicsComponent == nullptr) WARNING_LOG("Component Null");
		auto collisonComponent = GetComponent<kiko::CollisionComponent>();
		if (collisonComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();

			if (renderComponent) {
				float scale = transform.scale;
				collisonComponent->m_radius = renderComponent->GetRadius() * scale;
			}

		}

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		

		kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player) {
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}
	}

	void Enemy::OnCollissionEnter(Actor* other)
	{
	}

	void Enemy::OnCollissionExit(Actor* other) {

	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}