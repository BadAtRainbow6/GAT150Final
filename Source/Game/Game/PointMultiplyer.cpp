#include "PointMultiplyer.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"

void PointMultiplyer::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0,-1 }.Rotate(transform.rotation);
	transform.position += forward * m_speed * m_speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_Renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_Renderer.GetHeight());
}

void PointMultiplyer::OnCollissionEnter(Actor* other)
{
	if (other->tag == "Player") {
		m_game->SetMultiplyer(2);
		m_game->SetMultiplyerTimer(10.0f);

		m_destroyed = true;
	}
}
