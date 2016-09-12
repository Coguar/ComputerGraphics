#include "stdafx.h"
#include "Items.h"

CItem::CItem(IItem::type type)
{
	m_type = type;
}

IItem::type CItem::GetType() const
{
	return m_type;
}

const std::vector<glm::vec2> & CItem::GetContour() const
{
	return m_contour;
}

void CItem::AddPoint(glm::vec2 const & coord)
{
	m_contour.push_back(coord);
}

void CItem::SetColor(glm::vec4 const & color)
{
	m_color = color;
}

glm::vec4 CItem::GetColor() const
{
	return m_color;
}

void CItem::SetAngle(float angle)
{
	m_angle = angle;
}

float CItem::GetAngle()
{
	return m_angle;
}

ComplexItem::ComplexItem(glm::vec2 const & position)
	: m_position(position)
{
}

void ComplexItem::SetRadius(float rad)
{
	m_radius = rad;
}

void ComplexItem::AddItem(CItem const & item)
{
	m_items.push_back(item);
}

glm::vec2 ComplexItem::GetPosition() const
{
	return glm::vec2(m_position.x, m_position.y);
}

void ComplexItem::SetPosition(glm::vec2 const & position)
{
	m_position = position;
}

void ComplexItem::SetCenter(glm::vec2 const & center)
{
	m_center = center;
}

const std::vector<CItem>& ComplexItem::GetItemsList() const
{
	return m_items;
}

bool ComplexItem::HitTest(const glm::vec2 & point)
{
	float distance = std::sqrt(std::pow(point.x - (m_position.x + m_center.x), 2) + std::pow(point.y - (m_position.y + m_center.y), 2));
	if (distance <= m_radius)
	{
		return true;
	}
	return false;
}
