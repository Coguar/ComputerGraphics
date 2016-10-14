#pragma once
struct ITetrisListener
{
	virtual void onLosed() = 0;
	virtual void onScoreAdded(size_t score) = 0;
	virtual ~ITetrisListener() {};
};