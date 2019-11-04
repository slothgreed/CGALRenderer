#ifndef CGAL_POLYHEDRAL_SURFACE_H
#define CGAL_POLYHEDRAL_SURFACE_H

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Local_Kernel;
typedef Local_Kernel::Point_3 Local_Point;
typedef Local_Kernel::Vector_3 Local_Vector;
typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::Halfedge_handle HalfEdge_handle;
typedef typename Polyhedron::Traits Traits;
typedef typename Polyhedron::Halfedge_const_handle Halfedge_const_handle;
typedef typename Polyhedron::Vertex_const_handle Vertex_const_handle;
typedef typename Polyhedron::Facet_const_handle Facet_const_handle;

class VertexBuffer;
class CGALPolyhedron : CGALModel
{
public:
	CGALPolyhedron();
	~CGALPolyhedron();

	virtual void Load(const std::string& filePath);
	virtual void BuildDrawData();
	virtual void Draw();

private:
	void BuildFacet(const Facet_const_handle& facet, std::vector<glm::vec3>& position, std::vector<glm::vec3>& normal);
	void BuildEdge(const Halfedge_const_handle& edge, std::vector<glm::vec3>& position);
	void BuildVertex(const Vertex_const_handle& vertex);
	Local_Vector CalculateFaceNormal(const Halfedge_const_handle& halfEdge);
	Local_Vector CalculateVertexNormal(const Halfedge_const_handle& halfEdge);

	Polyhedron* m_model;
	HalfEdge_handle* m_halfEdge;
	VertexBuffer* m_pFaceVBO;
	VertexBuffer* m_pEdgeVBO;
};

#endif CGAL_POLYHEDRAL_SURFACE_H