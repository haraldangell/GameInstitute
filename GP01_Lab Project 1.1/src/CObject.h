#pragma once
#include "main.h"

class CVertex 
{
    public:
	CVertex(float fx, float fy, float fz) { x = fx; y = fy, z = fz; }
    CVertex() { x = 0.0f; y = 0.0f, z = 0.0f; }
    
	float x;
	float y;
	float z;
	ULONG       Diffuse;    // Diffuse vertex colour component
};

class CPolygon
{
    public:
	CPolygon(ULONG Count);
    CPolygon();
	virtual ~CPolygon();
    
	long AddVertex(ULONG Count = 1);
    
	ULONG m_nVertexCount;
	CVertex * m_pVertex;
};


class CMesh
{
    public:
	CMesh(ULONG Count);
    CMesh();
	virtual ~CMesh();
    
	long AddPolygon(ULONG Count = 1);
    
	ULONG m_nPolygonCount;
	CPolygon** m_pPolygon;
};


class CObject
{
    public:
	CObject(CMesh* pMesh);
    CObject();
    
	D3DXMATRIX m_mtxWorld;
	CMesh* m_pMesh;
};
