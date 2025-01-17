// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_3/Odt_move.h $
// $Id: Odt_move.h 60688 2011-01-10 15:43:22Z lrineau $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_3_ODT_MOVE_H
#define CGAL_MESH_3_ODT_MOVE_H

#include <CGAL/Mesh_3/Uniform_sizing_field.h>

#include <string>

namespace CGAL {


namespace Mesh_3 {
  

template <typename C3T3,
  typename SizingField = Uniform_sizing_field<typename C3T3::Triangulation> >
class Odt_move
{
  typedef typename C3T3::Triangulation Tr;
  typedef typename Tr::Geom_traits Gt;
  
  typedef typename Tr::Cell_handle Cell_handle;
  typedef typename Tr::Vertex_handle Vertex_handle;
  typedef typename Tr::Facet Facet;
  typedef typename Tr::Point Point_3;
  
  typedef typename std::vector<Cell_handle>   Cell_vector;
  typedef typename std::vector<Vertex_handle> Vertex_vector;
  typedef typename std::vector<Facet>         Facet_vector;
  
  typedef typename Gt::FT FT;
  typedef typename Gt::Vector_3 Vector_3;
  
public:
  typedef SizingField Sizing_field;
  
  Vector_3 operator()(const Vertex_handle& v,
                      const C3T3& c3t3,
                      const Sizing_field& sizing_field = Sizing_field()) const
  {
    // Don't move edge or corner vertices
    if ( c3t3.in_dimension(v) < 2 )
    {
      return CGAL::NULL_VECTOR;
    }
    
    // Compute move
    typename Gt::Construct_vector_3 vector =
      Gt().construct_vector_3_object();
    
    const Tr& tr = c3t3.triangulation();
    Vector_3 move = CGAL::NULL_VECTOR;
    FT sum_volume(0);
    
    Cell_vector incident_cells;
    tr.finite_incident_cells(v, std::back_inserter(incident_cells));
    
    const Point_3& p = v->point();
    
    for ( typename Cell_vector::iterator cit = incident_cells.begin() ;
         cit != incident_cells.end() ;
         ++cit )
    {
      const Cell_handle& cell = *cit;
      
      // Consider only cells of complex
      if ( ! c3t3.is_in_complex(cell) )
        continue;
      
      // Get points
      Point_3 circumcenter = tr.dual(cell);
      
      // Compute move
      Vector_3 p_circum = vector(p,circumcenter);
      FT volume = volume_quadrature(cell, tr, sizing_field);
      
      move = move + p_circum * volume;
      sum_volume += volume;
    }
    
    // Add boundary terms if needed
    if ( c3t3.in_dimension(v) == 2 )
    {
      //move = move + (1.0 / 12.0) * move_odt_2D(v, c3t3, sizing_field);
    }
    
    if ( FT(0) != sum_volume )
      return move/sum_volume;
    else
      return CGAL::NULL_VECTOR;
  }
  
  
#ifdef CGAL_MESH_3_OPTIMIZER_VERBOSE
  static std::string name() { return std::string("Odt"); }
#endif
  
private:
  // 1-point at cell centroid
  FT volume_quadrature(const Cell_handle& cell,
                       const Tr& tr,
                       const Sizing_field& sizing_field) const
  {
    typename Gt::Compute_volume_3 volume =
    Gt().compute_volume_3_object();
    
    typename Gt::Construct_centroid_3 centroid =
    Gt().construct_centroid_3_object();
    
    Point_3 c = centroid(tr.tetrahedron(cell));
    FT s = sizing_field(c,std::make_pair(cell,true));
    CGAL_assertion(!is_zero(s));

    // Points of cell are positively oriented
    FT abs_volume = volume(tr.tetrahedron(cell));
    CGAL_assertion(abs_volume >= 0);
    
    return abs_volume / (s*s*s);
  }
  
  
//  /**
//   * @class Is_on_c3t3_boundary
//   *
//   * A functor which returns false if a facet is on the boundary of c3t3
//   */
//  class Is_not_on_c3t3_boundary
//    {
//    public:
//      Is_not_on_c3t3_boundary(const C3T3& c3t3) : c3t3_(c3t3) { }
//      
//      bool operator()(const Facet& f) const
//      {
//        if (   ( ! c3t3_.is_in_complex(f) )
//            || ( c3t3_.is_in_complex(f.first)
//                && c3t3_.is_in_complex(f.first->neighbor(f.second)) ) )
//        {
//          return true;
//        }
//        
//        return false;
//      }
//      
//    private:
//      const C3T3& c3t3_;
//    };
//  
//  // boundary terms
//  Vector_3 move_odt_2D(const Vertex_handle& v,
//                       const C3T3& c3t3,
//                       const Sizing_field& sizing_field) const
//  {
//    // Triangulation
//    const Tr& tr = c3t3.triangulation();
//    
//    // Get boundary facets
//    Facet_vector incident_facets;
//    tr.finite_incident_facets(v, std::back_inserter(incident_facets));
//    
//    typename Facet_vector::iterator in_c3t3_incident_end = 
//      std::remove_if(incident_facets.begin(), incident_facets.end(),
//                     Is_not_on_c3t3_boundary(c3t3));
//    
//    // Compute boundary terms
//    Vector_3 move = CGAL::NULL_VECTOR;
//    for(typename Facet_vector::iterator fit = incident_facets.begin();
//        fit != in_c3t3_incident_end;
//        ++fit)
//    {
//      CGAL_assertion(c3t3.is_in_complex(*fit));
//      
//      // Normal
//      FT area = area_quadrature(*fit, tr, sizing_field);
//      Vector_3 facet_normal = area * normal_outside(*fit, c3t3);
//      
//      // Sq length
//      FT sq_length_sum = sq_length_facet_quadrature(v, *fit, sizing_field);       
//      
//      // Move
//      move = move + sq_length_sum * facet_normal;
//    }
//    
//    return move;
//  }
//
//  
//  // 1-point at facet centroid
//  FT area_quadrature(const Facet& facet,
//                     const Tr& tr,
//                     const Sizing_field& sizing_field) const
//  {
//    typename Gt::Compute_area_3 area =
//      Gt().compute_area_3_object();
//    
//    typename Gt::Construct_centroid_3 centroid =
//      Gt().construct_centroid_3_object();
//    
//    Point_3 c = centroid(tr.triangle(facet));
//    FT s = sizing_field(c, facet.first->vertex(0));
//    
//    return ( area(tr.triangle(facet)) / (s*s) );
//  }
//  
//  // 1-point at segment midpoint
//  FT sq_length_quadrature(const Vertex_handle& v1,
//                          const Vertex_handle& v2,
//                          const Sizing_field& sizing_field) const
//  {
//    typename Gt::Compute_squared_distance_3 sq_distance =
//      Gt().compute_squared_distance_3_object();
//    
//    typename Gt::Construct_midpoint_3 midpoint =
//      Gt().construct_midpoint_3_object();
//    
//    Point_3 c = midpoint(v1->point(), v2->point());
//    FT s = sizing_field(c,v1);
//    
//    return ( sq_distance(v1->point(), v2->point()) / s );
//  }
//  
//  
//  FT sq_length_facet_quadrature(const Vertex_handle& v,
//                                const Facet& f,
//                                const Sizing_field& sizing_field) const
//  {
//    // get indices
//    const int& vertex_index = f.first->index(v);
//    int k1 = (vertex_index+1)&3;
//    int k2 = (vertex_index+2)&3;
//    int k3 = (vertex_index+3)&3;
//    
//    if ( k2 == f.second ) { std::swap(k1,k2); }
//    else if ( k3 == f.second ) { std::swap(k1,k3); }  
//    
//    // Here k1 is opposite vertex index in f.first, facet vertices indices
//    // are (vertex_index,k2,k3)
//    
//    const Vertex_handle& v2 = f.first->vertex(k2);
//    const Vertex_handle& v3 = f.first->vertex(k3);
//    FT sqd_v2 = sq_length_quadrature(v, v2, sizing_field);
//    FT sqd_v3 = sq_length_quadrature(v, v3, sizing_field);
//    
//    return (sqd_v2 + sqd_v3);
//  }
//  
//  
//  Vector_3 normal_outside(const Facet& f, const C3T3& c3t3) const
//  {
//    typename Gt::Construct_normal_3 normal =
//      Gt().construct_normal_3_object();
//    
//    const Cell_handle& cell = f.first;
//    const int& i = f.second;
//    
//    int k1 = (i+1)&3;
//    int k2 = (i+2)&3;
//    int k3 = (i+3)&3;
//    
//    // Orient normals to the outside of cell
//    if ( (i&1) == 1 )
//      std::swap(k1,k2);
//    
//    // Make sure normals are oriented outside
//    if ( ! c3t3.is_in_complex(cell) )
//      std::swap(k1,k2);
//    
//    const Point_3& p1 = cell->vertex(k1)->point();
//    const Point_3& p2 = cell->vertex(k2)->point();
//    const Point_3& p3 = cell->vertex(k3)->point();
//    
//    return normal(p1,p2,p3);
//  }
  
  
};

} // end namespace Mesh_3


} //namespace CGAL

#endif // CGAL_MESH_3_ODT_MOVE_H
