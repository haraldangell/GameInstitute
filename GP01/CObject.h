#pragma once //COBJECT_H

#include "main.h"

class CVertex 
{
public:
	CVertex(float fX, float fY, float fZ) { x = fX; y = fY, z = fZ; }
	CVertex() { x = 0.0f; y = 0.0f, z = 0.0f; }

	float x;
	float y;
	float z;
};

class CPolygon
{
public:
	CPolygon(USHORT VertexCount);
	CPolygon();
	virtual ~CPolygon();

	long AddVertex(USHORT Count = 1);

	USHORT m_nVertexCount;
	CVertex * m_pVertex;
};

class CMesh {
public:
	CMesh(ULONG Count);
	CMesh();
	virtual ~CMesh();

	long AddPolygon(ULONG Count = 1);

	ULONG m_nPolygonCount;
	CPolygon ** m_pPolygon;
};

class CObject
{
public:
	CObject(CMesh * pMesh);
	CObject();

	D3DXMATRIX m_mtxWorld;
	CMesh	* m_pMesh;
};