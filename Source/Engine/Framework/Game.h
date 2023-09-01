#pragma once
#include <memory>

namespace kiko
{
	class Scene;
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += (points * m_PointMultiplyer); }

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }

		int GetMultiplyer() const { return m_PointMultiplyer; }
		void SetMultiplyer(int multiplyer) { m_PointMultiplyer = multiplyer; }

		float GetMultiplyerTimer() const { return m_MultiplyerTimer; }
		void SetMultiplyerTimer(float time) { m_MultiplyerTimer = time; }

	protected:
		std::unique_ptr<Scene> m_scene;


		int m_PointMultiplyer = 1;
		float m_MultiplyerTimer = 0;

		int m_score = 0;
		int m_lives = 0;
	};
}