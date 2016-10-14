#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{
	const std::vector<glm::vec4> COLORS =
	{
		{ 1, 1, 1, 0.8f },
		{ 1, 1, 0, 0.8f },
		{ 1, 0, 1, 0.8f },
		{ 1, 0, 0, 0.8f },
		{ 0, 1, 1, 0.8f },
		{ 0, 1, 0, 0.8f },
		{ 0, 0, 1, 0.8f },
	};

const std::vector<float> TYPE_COEFFICIENT = { 1, 1.226f, 2.2f };
const float ANIMATION_SPEED = 0.01f;

const glm::vec3 WHITE = { 1, 1, 1 };


const float FI = 1.618;
const std::vector<Vertex> PENTAKIS_VERTICIES =
{
	{ 1, 1, 1 }, //0
	{ 1, 1, -1 },//1
	{ 1, -1, 1 },//2
	{ 1, -1, -1 },//3
	{ -1, 1, 1 },//4
	{ -1, 1, -1 },//5
	{ -1, -1, 1 },//6
	{ -1, -1, -1 },//7

	{ 0, 1 / FI, FI },//8
	{ 0, 1 / FI, -FI },//9
	{ 0, -1 / FI, FI },//10
	{ 0, -1 / FI, -FI },//11

	{ 1 / FI, FI, 0 },//12
	{ 1 / FI, -FI,  0 },//13
	{ -1 / FI, FI, 0 },//14
	{ -1 / FI, -FI, 0 },//15

	{ FI, 0, 1 / FI },//16
	{-FI, 0, 1 / FI},//17
	{ FI, 0, -1 / FI},//18
	{-FI, 0, -1 / FI },//19
};

const std::vector<uint16_t> PENTAKIS_EDGES
{
	0, 12, 1, 18, 16, 
	0, 12, 14, 4, 8,
	0, 8, 10, 2, 16,
	0, 12,
	1, 9, 5, 14, 12, 
	1, 18, 3, 11, 9,
	5, 19, 17, 4, 14, 5,
	9, 11, 7, 19, 5, 19, 7,
	11, 3, 13, 15, 7, 15,
	6, 17, 6, 10, 2, 13

};

const std::vector<std::vector<uint16_t>> POLIGONS_VERTICIES =
{
	{0, 16, 18, 1, 12},
	{0, 12, 14, 4, 8},
	{0, 8, 10, 2, 16},
	{12, 1, 9, 5, 14},
	{5, 19, 17, 4, 14},
	{17, 19, 7, 15, 6},
	{15, 13, 2, 10, 6},
	{2, 13, 3, 18, 16},
	{18, 3, 11, 9, 1},
	{9, 11, 7, 19, 5},
	{11, 3, 13, 15, 7},
	{4, 17, 6, 10, 8}

};


/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetRotateZTransfrom(float phase)
{
    // угол вращения вокруг оси Z лежит в отрезке [0...2*pi].
    const float angle = float(2 * M_PI) * phase;

    return glm::rotate(glm::mat4(), angle, {0, 0, 1});
}

/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetScalingPulseTransform(float phase)
{
    // число пульсаций размера - произвольная константа.
    const int pulseCount = 4;
    float scale = fabsf(cosf(float(pulseCount * M_PI) * phase));

    return glm::scale(glm::mat4(), {scale, scale, scale});
}

/// @param phase - Фаза анимации на отрезке [0..1]
glm::mat4 GetBounceTransform(float phase)
{
    // начальная скорость и число отскоков - произвольные константы.
    const int bounceCount = 4;
    const float startSpeed = 15.f;
    // "время" пробегает bounceCount раз по отрезку [0...1/bounceCount].
    const float time = fmodf(phase, 1.f / float(bounceCount));
    // ускорение подбирается так, чтобы на 0.25с скорость стала
    // противоположна начальной.
    const float acceleration = - (startSpeed * 2.f * float(bounceCount));
    // расстояние - результат интегрирования функции скорости:
    //  speed = startSpeed + acceleration * time;
    float offset = time * (startSpeed + 0.5f * acceleration * time);

    // для отскоков с нечётным номером меняем знак.
    const int bounceNo = int(phase * bounceCount);
    if (bounceNo % 2)
    {
        offset = -offset;
    }

    return glm::translate(glm::mat4(), {offset, 0.f, 0.f});
}

glm::vec3 GetCenterOfPoints(glm::vec3 const& p1, glm::vec3 const& p2)
{
	return glm::vec3((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, (p1.z + p2.z) / 2);
}

void WriteIntoVerticles(std::vector<uint16_t> const& poligon, std::vector<Vertex> & verticles)
{
	glm::vec3 point = verticles[poligon[3]];
	float length = glm::distance(GetCenterOfPoints(verticles[poligon[0]], verticles[poligon[1]]), verticles[poligon[3]]);
	float radius = glm::distance(verticles[poligon[0]], verticles[poligon[1]]) / (2 * std::sin(0.2 * M_PI));
	glm::vec3 vec = GetCenterOfPoints(verticles[poligon[0]], verticles[poligon[1]]) - point;
	float k = radius / length;
	point.x = point.x + vec.x * k;
	point.y = point.y + vec.y * k;
	point.z = point.z + vec.z * k;

	verticles.push_back({ point});
}

void WriteIntoFaces(std::vector<uint16_t> & faces, std::vector<uint16_t> const& poligon, uint16_t vertexNum)
{
	for (size_t i = 0; i < poligon.size(); ++i)
	{
		faces.push_back(poligon[i]);
		if (i + 1 != poligon.size())
		{
			faces.push_back(poligon[i + 1]);
		}
		else
		{
			faces.push_back(poligon[0]);
		}
		faces.push_back(vertexNum);
	}
}
}
CPentakis::CPentakis()
{
	InitPentakis();
}

void CPentakis::InitPentakis()
{
	m_verticies = PENTAKIS_VERTICIES;
	for (auto &it : POLIGONS_VERTICIES)
	{
		WriteIntoVerticles(it, m_verticies);
		WriteIntoFaces(m_pentakisFaces, it, m_verticies.size() - 1);
	}
	m_sourceVerticies = m_verticies;
}

void CPentakis::CheckType()
{
	for (size_t i = 20; i < m_verticies.size(); ++i)
	{
		auto normVec = glm::normalize(m_sourceVerticies[i]);
		m_verticies[i] = normVec;
		auto dist = glm::distance(m_sourceVerticies[i], { 0, 0, 0 });
		float k = 0;
		k = m_currentPickLvl * dist;

		m_verticies[i].x = m_verticies[i].x * k;
		m_verticies[i].y = m_verticies[i].y * k;
		m_verticies[i].z = m_verticies[i].z * k;

	}
}

void CPentakis::NextType()
{
	typeWasChanged = true;
	switch (m_type)
	{
	case CPentakis::DODECAHEDRON:
		m_type = PENTAKIS;
		break;
	case CPentakis::PENTAKIS:
		m_type = STAR;
		break;
	case CPentakis::STAR:
		m_type = DODECAHEDRON;
		break;
	default:
		break;
	}
	SetSpeed();
}

const std::vector<Vertex>& CPentakis::GetVerticies() const
{
	return m_verticies;
}

const std::vector<uint16_t>& CPentakis::GetFaces() const
{
	return m_pentakisFaces;
}

const CPentakis::Type CPentakis::GetType() const
{
	return m_type;
}

const std::vector<uint16_t>& CPentakis::GetEdgesFaces() const
{
	if (m_type == CPentakis::DODECAHEDRON)
	{
		return PENTAKIS_EDGES;
	}
	else
	{
		return m_pentakisFaces;
	}
}


//TODO return glm::vec4
std::function<glm::vec4()> CPentakis::GetColoroid() const
{
	size_t count = 0;
	size_t current = 0;
	size_t typeCounter = 3;
	if (m_type == Type::DODECAHEDRON)
	{
		typeCounter *= 5;
	}
	auto func = [count, current, typeCounter]() mutable
	{
		auto color = COLORS[current];
		count++;
		if (count >= typeCounter)
		{
			current = (current + 1) % COLORS.size();
			count = 0;
		}
		return color;
	};
	return func;
}

void CPentakis::SetSpeed()
{
	int sign = TYPE_COEFFICIENT[m_type] - m_currentPickLvl < 0 ? -1 : 1;
	m_animSpeed = ANIMATION_SPEED * sign;
}

void CPentakis::SetPickLvl()
{
	if (m_currentPickLvl == TYPE_COEFFICIENT[m_type])
		return;
	m_currentPickLvl += m_animSpeed;
	if (m_animSpeed < 0 && m_currentPickLvl < TYPE_COEFFICIENT[m_type] || m_animSpeed > 0 && m_currentPickLvl > TYPE_COEFFICIENT[m_type])
	{
		m_currentPickLvl = TYPE_COEFFICIENT[m_type];
		typeWasChanged = false;

	}
}

void CPentakis::Update(float deltaTime)
{
	(void)deltaTime;
	SetPickLvl();
	if (typeWasChanged)
	{
		CheckType();
	}
}
