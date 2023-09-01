#include "Asteroid.h"
#include "SpaceGame.h"
#include "PointMultiplyer.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Framework/Scene.h"
#include "Core/Math/MathUtils.h"
#include "Framework/Emitter.h"
#include "Core/Random.h"

void Asteroid::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);
	transform.position += forward * m_speed * m_speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_Renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_Renderer.GetHeight());
}

void Asteroid::OnCollissionEnter(Actor* other)
{
 	if (other->tag == "PlayerBullet") {
		m_health -= 10;
		if (m_health == 0)
		{
  			m_game->AddPoints(200);
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
			kiko::Transform transformE{ {transform.position }, 0, 1 };
			auto emitter = std::make_unique<kiko::Emitter>(transformE, data);
			emitter->SetLifespan(1.0f);
			m_scene->Add(std::move(emitter));

			if (kiko::random(10) <= 2) {
				kiko::Transform transform{ transform.position, 0, 3};
				std::unique_ptr<PointMultiplyer> multiplyer = std::make_unique<PointMultiplyer>(2.0f, transform, kiko::g_manager.Get("multiplyer.txt"));
				multiplyer->tag = "Multiplyer";
				multiplyer->m_game = m_game;
				m_scene->Add(std::move(multiplyer));
			}
		

		}
	}

	if (other->tag == "Player") {
		m_game->AddPoints(200);
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
		kiko::Transform transformE{ {transform.position }, 0, 1 };
		auto emitter = std::make_unique<kiko::Emitter>(transformE, data);
		emitter->SetLifespan(1.0f);
		m_scene->Add(std::move(emitter));


		if (kiko::random(10) <= 2) {
			kiko::Transform transform{ transform.position, 0, 3};
			std::unique_ptr<PointMultiplyer> multiplyer = std::make_unique<PointMultiplyer>(2.0f, transform, kiko::g_manager.Get("multiplyer.txt"));
			multiplyer->tag = "Multiplyer";
			multiplyer->m_game = m_game;
			m_scene->Add(std::move(multiplyer));
		}
	}


}
