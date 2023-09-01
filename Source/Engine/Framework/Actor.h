#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Components/Component.h"
#include <memory>

namespace kiko
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const kiko::Transform& transform, std::shared_ptr<Model> model) :
		transform{ transform }
		{}
		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; }

		virtual void OnCollissionEnter(Actor* other) {}
		virtual void OnCollissionExit(Actor* other) {}



		float GetLifespan() const { return lifespan; }
		void SetLifespan(float lifespan) { lifespan = lifespan; }


		class Scene* m_scene = nullptr;
		friend class Scene;
		friend class Game;


	public:

		kiko::Transform transform;
		std::string tag;

		float lifespan = -1.0f;
		bool persistent = false;
		bool prototype = false;
		bool m_destroyed = false;
		

		class Game* m_game = nullptr;

	protected:
		std::vector<std::unique_ptr<Component>> components;
	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}


		return nullptr;
	}
}