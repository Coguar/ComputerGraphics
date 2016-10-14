#include "stdafx.h"
#include "FlashingText.h"





CFlashingText::CFlashingText(float timePeriod, glm::vec2 pos, std::string const & text)
	: m_position(pos)
	, m_timePeriod(timePeriod)
	, m_text(text)
{
}

CFlashingText::~CFlashingText()
{
}

void CFlashingText::CheckVsibility()
{
	if (m_deltaTime >= m_timePeriod)
	{
		m_deltaTime = 0;
		m_needShow = !m_needShow;
	}
}

void CFlashingText::Update(float dt)
{
	m_deltaTime += dt;
	CheckVsibility();
}

const glm::vec2 CFlashingText::GetPosition() const
{
	return m_position;
}

const std::string & CFlashingText::GetText() const
{
	return m_text;
}

const bool CFlashingText::IsVisible() const
{
	return m_needShow;
}
