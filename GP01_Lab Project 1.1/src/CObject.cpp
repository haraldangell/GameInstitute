#include "CObject.h"


//Objects
CObject::CObject()
{
	m_pMesh = nullptr;
	D3DXMatrixIdentity(&m_mtxWorld);
}
CObject::CObject(CMesh* pMesh)
{
	D3DXMatrixIdentity(&m_mtxWorld);
    
	m_pMesh = pMesh;
}
//Mesh
CMesh::CMesh()
{
	m_nPolygonCount = 0;
	m_pPolygon = nullptr;
}
CMesh::CMesh(ULONG Count)
{
	m_nPolygonCount = 0;
	m_pPolygon = nullptr;
    
	AddPolygon(Count);
}
CMesh::~CMesh()
{
	if (m_pPolygon) delete[]m_pPolygon;
    
	m_nPolygonCount = 0;
	m_pPolygon = nullptr;
}
long CMesh::AddPolygon(ULONG Count)
{
	//See addvertex to understand if you dont get it
    
	CPolygon** pPolyBuffer = nullptr;
    
	if (!(pPolyBuffer = new CPolygon * [m_nPolygonCount + Count])) return -1;
    
	//ZeroMemory Fills a block of memory with zeros.
	ZeroMemory(&pPolyBuffer[m_nPolygonCount], Count * sizeof(CPolygon*));
    
	if (m_pPolygon)
	{
		memcpy(pPolyBuffer, m_pPolygon, m_nPolygonCount * sizeof(CPolygon*));
		delete[] m_pPolygon;
	}
	m_pPolygon = pPolyBuffer;
    
	for (UINT i = 0; i < Count; i++)
	{
		// Allocate new poly
		if (!(m_pPolygon[m_nPolygonCount] = new CPolygon())) return -1;
        
		// Increase overall poly count
		m_nPolygonCount++;
        
	}
	return m_nPolygonCount - Count;
}
//Polygon
CPolygon::CPolygon()
{
	m_nVertexCount = 0;
	m_pVertex = nullptr;
}
CPolygon::CPolygon(ULONG Count)
{
	m_nVertexCount = 0;
	m_pVertex = nullptr;
    
	AddVertex(Count);
}
CPolygon::~CPolygon()
{
	if (m_pVertex) delete[]m_pVertex;
    
	m_pVertex = nullptr;
	m_nVertexCount = 0;
}
long CPolygon::AddVertex(ULONG Count)
{
	CVertex* pVertexBuffer = nullptr;
    
    
	//Builds a new empty array, with the count from before and the count you want to add,
	//and if the program is not able to create that array it will return with a -1
	if (!(pVertexBuffer = new CVertex[m_nVertexCount + Count])) return -1;
    
	//If is true if it's not null, so i if it's true it needs to copy the old array into the buffer.
	//when we have copied the array into the buffer, we delete/release the content of the array.
	if (m_pVertex)
	{
		memcpy(pVertexBuffer, m_pVertex, m_nVertexCount * sizeof(CVertex));
		delete[]m_pVertex;
	}
    
	m_pVertex = pVertexBuffer;
	m_nVertexCount += Count;
    
	//Delete pVertexBuffer since it was newed up.
	//delete[]pVertexBuffer;
	//pVertexBuffer = nullptr;
    
	return m_nVertexCount - Count;
}
//Vertex
//All has been taken care off in the  header file