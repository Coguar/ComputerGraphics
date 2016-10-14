#include "stdafx.h"
#include "FunctionSurface.h"
#include <algorithm>

namespace
{
const float DOT_SIZE = 5.f;

// вычисляет нормали численным методом,
// с помощью векторного произведения.
void CalculateNormals(std::vector<SVertexP3N> &vertices,
                      const Function2D &fn, float step,
						float u, float v)
{
	SVertexP3N v1 = vertices[vertices.size() - 1];
	glm::vec3 normV1 = fn(u, v + step) - v1.position;
	glm::vec3 normV2 = fn(u + step, v ) - v1.position;
	vertices[vertices.size() - 1].normal = glm::normalize(glm::cross(normV1, normV2));
}

/// Привязывает вершины к состоянию OpenGL,
/// затем вызывает 'callback'.
template <class T>
void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
{
    // Включаем режим vertex array и normal array.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Выполняем привязку vertex array и normal array
    const size_t stride = sizeof(SVertexP3N);
    glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
    glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

    // Выполняем внешнюю функцию.
    callback();

    // Выключаем режим vertex array и normal array.
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
                                    unsigned columnCount, unsigned rowCount)
{
    indicies.clear();
    indicies.reserve((columnCount - 1) * rowCount * 2);
    // вычисляем индексы вершин.
    for (unsigned ci = 0; ci < columnCount - 1; ++ci)
    {
        if (ci % 2 == 0)
        {
            for (unsigned ri = 0; ri < rowCount; ++ri)
            {
                unsigned index = ci * rowCount + ri;
                indicies.push_back(index + rowCount);
                indicies.push_back(index);
            }
        }
        else
        {
            for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
            {
                unsigned index = ci * rowCount + ri;
                indicies.push_back(index);
                indicies.push_back(index + rowCount);
            }
        }
    }
	unsigned ci = columnCount - 1;
	if (ci % 2 == 0)
	{
		for (unsigned ri = 0; ri < rowCount; ++ri)
		{
			unsigned index = ci * rowCount + ri;
			indicies.push_back(rowCount - 1 - ri);
			indicies.push_back(index);
		}
	}
	else
	{
		for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
		{
			unsigned index = ci * rowCount + ri;
			indicies.push_back(index);
			indicies.push_back(rowCount - ri - 1);
		}
	}
}


const glm::vec3 MAX_COLOR = { 0, 0.5, 1 };
const glm::vec3 MIN_COLOR = { 1, 0.5, 0 };

// Приводит значение от входного диапазона к диапазону [0;1]
float NormalizeValue(float value, glm::vec2 const& range)
{
	const float length = (std::abs(range.x - range.y));
	return std::abs(range.y - value) / length;
}

void ApplyColor(glm::vec2 const& range, float param)
{
	const float normalizedY = NormalizeValue(param, range);
	const auto color = MAX_COLOR * (1 - normalizedY) + MIN_COLOR * normalizedY;
	glColor3f(color.x, color.y, color.z);
}
}

CDottedFunctionSurface::CDottedFunctionSurface(const Function2D &fn)
    : m_fn(fn)
{
}

void CDottedFunctionSurface::Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step)
{
    m_vertices.clear();
    // вычисляем позиции вершин.
    for (float x = rangeX.x; x <= rangeX.y; x += step)
    {
        for (float z = rangeZ.x; z <= rangeZ.y; z += step)
        {
            m_vertices.push_back(m_fn(x, z));
			CalculateNormals(m_vertices, m_fn, step, x, z);
        }
    }
	m_vertices.push_back(m_fn(rangeX.y, rangeZ.y));

    
}

void CDottedFunctionSurface::Draw() const
{
    glPointSize(DOT_SIZE);
    DoWithBindedArrays(m_vertices, [this] {
        glDrawArrays(GL_POINTS, 0, GLsizei(m_vertices.size()));
    });
}

CSolidFunctionSurface::CSolidFunctionSurface(const Function2D &fn)
    : m_fn(fn)
	, isEdgeOnly(true)
{
}

void CSolidFunctionSurface::Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step)
{
    const unsigned columnCount = unsigned((rangeX.y - rangeX.x) / step);
    const unsigned rowCount = unsigned((rangeZ.y - rangeZ.x) / step);
    m_vertices.clear();
    m_vertices.reserve(columnCount * rowCount);

    // вычисляем позиции вершин.
    for (unsigned ci = 0; ci < columnCount; ++ci)
    {
        const float x = rangeX.x + step * float(ci);
        for (unsigned ri = 0; ri < rowCount; ++ri)
        {
            const float z = rangeZ.x + step * float(ri);
            m_vertices.push_back(m_fn( x, z));
			float yParam = m_vertices[m_vertices.size() - 1].position.y;
			m_range.y = std::min(yParam, m_range.y);
			m_range.x = std::max(yParam, m_range.x);

			CalculateNormals(m_vertices, m_fn, step, x, z);
        }
    }
    CalculateTriangleStripIndicies(m_indicies, columnCount, rowCount);
}


void DrawFunction(std::vector<uint32_t> const& indicies, std::vector<SVertexP3N> const& verticies, glm::vec2 const& range, bool isColored)
{
	for (auto &it : indicies)
	{
		auto v = verticies[it];
		if (isColored)
		{
			ApplyColor(range, v.position.y);
		}
		else
		{
			glColor3f(1, 1, 1);
		}
		glVertex3f(v.position.x, v.position.y, v.position.z);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);

	}
}

void CSolidFunctionSurface::Draw() const
{

	auto mode = GL_TRIANGLE_STRIP;
	if (isEdgeOnly)
	{
		mode = GL_LINE_STRIP;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glBegin(mode);
	DrawFunction(m_indicies, m_vertices, m_range, isColored);
	glEnd();
	glCullFace(GL_BACK);
	glBegin(mode);
	DrawFunction(m_indicies, m_vertices, m_range, isColored);
	glEnd();
}

void CSolidFunctionSurface::ChangeMode()
{
	isEdgeOnly = !isEdgeOnly;
}

void CSolidFunctionSurface::ChangeColorMode()
{
	isColored = !isColored;
}
