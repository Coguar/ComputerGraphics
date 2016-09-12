#pragma once
#include <vector>
#include "Items.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

class CFileReader
{
public:
	CFileReader();
	~CFileReader();
	static ComplexItem ReadFromJsonFile(std::string const& fileName);
	static CItem InitCircle(boost::property_tree::ptree & pt);
	static CItem InitComplexShape(boost::property_tree::ptree & pt, IItem::type type);
};

