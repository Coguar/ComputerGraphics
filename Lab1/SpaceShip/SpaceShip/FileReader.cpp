#include "stdafx.h"
#include "FileReader.h"
#include <algorithm>
namespace
{
	glm::vec2 RotateItemsPoint(float angle, float x, float y)
	{
		const float rotateX = x * cosf(angle) - y * sinf(angle);
		const float rotateY = x * sinf(angle) + y * cosf(angle);
		return glm::vec2(rotateX, rotateY);
	}

	float StringToFloat(std::string const& str)
	{
		float number = std::strtof(str.c_str(), nullptr);
		return number;
	}
}

CFileReader::CFileReader()
{
}


CFileReader::~CFileReader()
{
}

ComplexItem CFileReader::ReadFromJsonFile(std::string const & fileName)
{
	try
	{
		ComplexItem complexItem({ 400, 300 });
		std::ifstream ss(fileName);

		boost::property_tree::ptree pt;
		boost::property_tree::read_json(ss, pt);
		complexItem.SetCenter({ StringToFloat(pt.get_child("CenterX").data()), StringToFloat(pt.get_child("CenterY").data()) });
		complexItem.SetRadius(StringToFloat(pt.get_child("radius").data()));
		for(auto &v: pt.get_child("items"))
		{
			if (v.second.get_child("type").data() == "circle")
			{
				complexItem.AddItem(InitCircle(v.second));
			}
			else if (v.second.get_child("type").data() == "complex")
			{
				complexItem.AddItem(InitComplexShape(v.second, IItem::type::Complex));
			}
			else if (v.second.get_child("type").data() == "line")
			{
				complexItem.AddItem(InitComplexShape(v.second, IItem::type::Line));
			}
		}
		return complexItem;
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ComplexItem();
}

CItem CFileReader::InitCircle(boost::property_tree::ptree & pt)
{
	CItem item(IItem::type::Circle);
	std::vector<float> color;

	float rotate = StringToFloat(pt.get_child("angle").data());
	rotate = float(rotate * M_PI / 180);
	item.SetAngle(rotate);

	//TO DO replace BOOST_FOREACH
	//*std transform / boost transform with std::back_inserter
	for (auto &it : pt.get_child("color"))
	{
		color.push_back(StringToFloat(it.second.data()));
	}

	item.SetColor({ color[0], color[1], color[2], color[3] });
	float rx = 0;
	float ry = 0;
	float xCenter = 0;
	float yCenter = 0;
	for(auto &par: pt.get_child("params"))
	{
		rx = StringToFloat(par.second.get_child("width").data());
		ry = StringToFloat(par.second.get_child("height").data());
		xCenter = StringToFloat(par.second.get_child("x").data());
		yCenter = StringToFloat(par.second.get_child("y").data());
	}
	const float step = float(2 * M_PI / 360);
	for (float angle = 0; angle <= float(2 * M_PI) ; angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);

		glm::vec2 point = RotateItemsPoint(rotate, dx, dy);
		item.AddPoint({ point.x + xCenter, point.y + yCenter });
	}
	return item;
}

CItem CFileReader::InitComplexShape(boost::property_tree::ptree & pt, IItem::type type)
{
	CItem item(type);
	std::vector<float> color;

	float rotate = StringToFloat(pt.get_child("angle").data());
	rotate = float(rotate * M_PI / 180);
	item.SetAngle(rotate);

	for(auto &col: pt.get_child("color"))
	{
		color.push_back(StringToFloat(col.second.data()));
	}
	item.SetColor({ color[0], color[1], color[2], color[3] });
	for(auto &v: pt.get_child("points"))
	{
		std::vector<float> coordinate;
		for(auto &t: v.second)
		{
			coordinate.push_back(StringToFloat(t.second.data()));
		}
		item.AddPoint(RotateItemsPoint(rotate, coordinate[0], coordinate[1]));
	}
	return item;
}


