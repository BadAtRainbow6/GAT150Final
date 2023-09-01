#include "Enemey.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Player.h"
#include "Weapon.h"
#include "Audio/AudioSystem.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Framework/Components/PhysicsComponent.h"


namespace kiko {
	CLASS_DEFINITION(Enemey)

	bool Enemey::Initialize()
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

	void Enemey::Update(float dt)
	{
		Actor::Update(dt);

		SetFaceingPlayer(false);

		kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player) {
			kiko::Vector2 direction = player->transform.position - transform.position;
			//turn torwards player
			float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
			//	transform.rotation += turnAngle * dt;
			m_physicsComponent->ApplyTorque(turnAngle);
			//check if player is in front
			if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
			{
				SetFaceingPlayer(true);
			}
		}

		m_physicsComponent->ApplyForce(forward * speed);

		//transform.position += forward * m_speed * m_speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_Renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_Renderer.GetHeight());

		m_fireTimer -= kiko::g_time.GetDeltaTime();

		/*if (m_fireTimer <= 0 && GetFaceingPlayer()) {
			kiko::Transform m_transform{ transform.position, transform.rotation, 1};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f, m_transform);
			weapon->tag = "EnemeyBullet";


			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComponent));

			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			kiko::g_AudioSystem.PlayOneShot("laser");

			m_fireTimer = m_fireTime;
		}*/
	}

	void Enemey::OnCollissionEnter(Actor* other)
	{
		if (other->tag == "PlayerBullet") {
			m_health -= 10;
			if (m_health <= 0) {
				kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
				//m_game->AddPoints(100);
				m_destroyed = true;


				kiko::EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 0;
				data.angle = 0;
				data.angleRange = kiko::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMax = 1.5f;
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = kiko::Color{ 0, 1, 0, 1 };
				kiko::Transform transform{ {transform.position }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->SetLifespan(1.0f);
				m_scene->Add(std::move(emitter));

				//add explosion with emitter here
				//spawnrate 0, position enemy position
			}
		}
		if (other->tag == "Player") {
			m_health = 0;
			if (m_health <= 0) {
				kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
				//m_game->AddPoints(100);
				m_destroyed = true;


				kiko::EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 0;
				data.angle = 0;
				data.angleRange = kiko::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMax = 1.5f;
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = kiko::Color{ 0, 1, 0, 1 };


				kiko::Transform transform{ {this->transform.position }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->SetLifespan(1.0f);
				m_scene->Add(std::move(emitter));

				//add explosion with emitter here
				//spawnrate 0, position enemy position
			}
		}
	}

	void Enemey::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}