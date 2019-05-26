#pragma once
class ScoreKeeper final : public dae::Singleton<ScoreKeeper>
{
public:
	void AddScore(int score) { m_Score += score; }
	int GetScore() { return m_Score; }
	void ResetScore() { m_Score = 0; }

	int GetLives() { return m_Lives; }
	void SetLives(int lives) { m_Lives = lives; }
private:
	int m_Score{};
	int m_Lives{};
};

