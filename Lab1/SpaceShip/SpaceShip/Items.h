#pragma once
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec4.hpp>

struct IItem
{
	enum type {
		Circle = 0,
		Ellipse,
		Complex,
		Line,
	} m_type;
	virtual void SetColor(glm::vec4 const& color) = 0;
	virtual glm::vec4 GetColor() const = 0;

	virtual type GetType() const = 0;
	virtual const std::vector<glm::vec2> & GetContour() const = 0;
	virtual void AddPoint(glm::vec2 const& coord) = 0;
	virtual ~IItem() = default;
};

class CItem : public IItem
{
public:
	CItem(IItem::type type);
	type GetType() const override;
	const std::vector<glm::vec2> & GetContour() const override;
	void AddPoint(glm::vec2 const& coord) override;
	void SetColor(glm::vec4 const& color) override;
	glm::vec4 GetColor() const override;
	void SetAngle(float angle);
	float GetAngle();
private:
	std::vector<glm::vec2> m_contour;
	glm::vec4 m_color;
	float m_angle = 0;
};

class ComplexItem
{
public:
	ComplexItem() = default;
	ComplexItem(glm::vec2 const& position);
	void SetRadius(float rad);
	void AddItem(CItem const& item);
	glm::vec2 GetPosition() const;
	void SetPosition(glm::vec2 const& position);
	void SetCenter(glm::vec2 const& center);
	const std::vector<CItem> & GetItemsList() const;
	
	bool HitTest(const glm::vec2 &point);
private:
	std::vector<CItem> m_items;
	glm::vec2 m_position;
	float m_radius = 0;
	glm::vec2 m_center;
};