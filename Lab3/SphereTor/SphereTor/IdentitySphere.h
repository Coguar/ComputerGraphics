#pragma once

#include "MeshP3NT2.h"
#include "libchapter3.h"

class CIdentitySphere final : public ISceneObject
{
public:
    CIdentitySphere(unsigned slices, unsigned stacks);

    void Update(float) final {}
    void Draw()const final;

private:
    void Tesselate(unsigned slices, unsigned stacks);

    SMeshP3NT2 m_mesh;
};

class CTor final : public ISceneObject
{
public:
	CTor(unsigned slices, unsigned stacks);

	void Update(float) final {}
	void Draw()const final;

private:
	void Tesselate(unsigned slices, unsigned stacks);

	SMeshP3NT2 m_mesh;
};

class CField final : public ISceneObject
{
public:
	CField(unsigned slices, unsigned stacks);

	void Update(float) final {}
	void Draw()const final;
private:
	void Tesselate(unsigned slices, unsigned stacks);

	SMeshP3NT2 m_mesh;
};