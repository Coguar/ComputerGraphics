#pragma once
class CFlashingText
{
public:
	CFlashingText() = default;
	CFlashingText(float timePeriod, glm::vec2 pos, std::string const& text);
	~CFlashingText();

	void Update(float dt);

	const glm::vec2 GetPosition() const;
	const std::string & GetText() const;
	const bool IsVisible() const;
private:
	void CheckVsibility();


	bool m_needShow = false;
	float m_timePeriod;
	float m_deltaTime = 0;
	std::string m_text;

	glm::vec2 m_position;
};

