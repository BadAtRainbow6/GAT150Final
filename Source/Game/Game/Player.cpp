#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include"Renderer/ModelManager.h"
#include "Weapon.h"
#include "Audio/AudioSystem.h"
#include "SpaceGame.h"
#include "Core/Math/MathUtils.h"


#include "Framework/Framework.h"

namespace kiko {
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
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

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		float rotate = 0;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);

		//m_transform.position += forward * speed * thrust * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_Renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_Renderer.GetHeight());

		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

			auto weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { this->transform.position, this->transform.rotation /*+ kiko::DegreesToRadians(10.0f)*/ , 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));



			//kiko::Transform m_transform{ transform.position, transform.rotation /*+ kiko::DegreesToRadians(10.0f)*/ , 1};
			//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f , m_transform);
			//weapon->tag = "PlayerBullet";

			//auto component = CREATE_CLASS(SpriteComponent)
			//component->m_texture = GET_RESOURCE(kiko::Texture, "rocket.png", kiko::g_Renderer);
			//weapon->AddComponent(std::move(component));

			//auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			//collisionComponent->m_radius = 30.0f;
			//weapon->AddComponent(std::move(collisionComponent));

			//weapon->Initialize();
			//m_scene->Add(std::move(weapon));
			//kiko::g_AudioSystem.PlayOneShot("laser");

			/*kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(10.0f), 1};
			weapon = std::make_unique<Weapon>(40.0f, transform2);
			weapon->m_tag = "PlayerBullet";
			m_scene->Add(std::move(weapon));
			kiko::g_AudioSystem.PlayOneShot("laser");*/
		}

		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
		else kiko::g_time.SetTimeScale(1.0f);


	}
	void Player::OnCollissionEnter(Actor* other)
	{
		if (other->tag == "EnemeyBullet") {
			m_health -= 10;
			if (m_health <= 0) {
				//m_game->SetLives(m_game->GetLives() - 1);
				kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
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
				data.color = kiko::Color{ 1, 0, 0, 1 };
				kiko::Transform transform{ {transform.position }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->SetLifespan(1.0f);
				m_scene->Add(std::move(emitter));


				dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			}
		}

		if (other->tag == "Enemey" || other->tag == "Asteroid") {
			m_health -= 50;
			if (m_health <= 0) {
				//m_game->SetLives(m_game->GetLives() - 1);
				kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
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
				data.color = kiko::Color{ 1, 0, 0, 1 };
				kiko::Transform transform{ {transform.position }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->SetLifespan(1.0f);
				m_scene->Add(std::move(emitter));

				dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			}
		}
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}



//if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
//	kiko::g_AudioSystem.PlayOneShot("laser");
//}