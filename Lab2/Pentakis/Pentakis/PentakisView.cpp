#include "stdafx.h"
#include "PentakisView.h"

namespace
{

	void CalcNormal(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3)
	{
		glm::vec3 v1 = p2 - p1;
		glm::vec3 v2 = p3 - p1;
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);
		glNormal3fv(glm::value_ptr(normal));
	}

	void DrawEdges(CPentakis const & pentakis)
	{
		glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 0, 1);
		for (uint16_t i : pentakis.GetEdgesFaces())
		{
			const Vertex &v = pentakis.GetVerticies()[i];
			glVertex3f(v.x, v.y, v.z);
		}
		glEnd();
	}

	void DrawObject(CPentakis const & pentakis)
	{
		auto coloroid = pentakis.GetColoroid();

		auto faces = pentakis.GetFaces();
		auto verticies = pentakis.GetVerticies();
		auto type = pentakis.GetType();

		std::vector<glm::vec3> triangleVerticies;
		for (uint16_t i : faces)
		{
			const Vertex &v = verticies[i];
			glColor4fv(glm::value_ptr(coloroid()));
			triangleVerticies.push_back(v);
			if (triangleVerticies.size() == 3)
			{
				CalcNormal(triangleVerticies[0], triangleVerticies[1], triangleVerticies[2]);
				triangleVerticies.clear();
			}
			glVertex3fv(glm::value_ptr(v));
		}
	}

	void DrawTriangles(CPentakis const & pentakis)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glBegin(GL_TRIANGLES);
		DrawObject(pentakis);
		glEnd();

		glEnable(GL_LIGHTING);
		glCullFace(GL_BACK);
		glBegin(GL_TRIANGLES);
		DrawObject(pentakis);
		glEnd();
		glDisable(GL_LIGHTING);
	}
}

void CPentakisView::DrawPentakis(CPentakis const & pentakis)
{
	DrawEdges(pentakis);
	DrawTriangles(pentakis);
}
