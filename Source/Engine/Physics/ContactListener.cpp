#include "ContactListener.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko {
	void kiko::ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->m_destroyed || actorB->m_destroyed) return;


			actorA->OnCollissionEnter(actorB);
			actorB->OnCollissionEnter(actorA);

			
		}
	}

	void kiko::ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->m_destroyed || actorB->m_destroyed) return;


			actorA->OnCollissionExit(actorB);
			actorB->OnCollissionExit(actorA);


		}
	}
}