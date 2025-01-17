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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_complex_3_in_triangulation_3.h $
// $Id: Mesh_complex_3_in_triangulation_3.h 60688 2011-01-10 15:43:22Z lrineau $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_COMPLEX_3_IN_TRIANGULATION_3_H
#define CGAL_MESH_COMPLEX_3_IN_TRIANGULATION_3_H

#include <map>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <CGAL/iterator.h>

#include <CGAL/Mesh_3/utilities.h>
#include <CGAL/Mesh_3/Mesh_complex_3_in_triangulation_3_base.h>


namespace CGAL {


template <typename Tr,
          typename CornerIndex = int,
          typename CurveSegmentIndex = int>
class Mesh_complex_3_in_triangulation_3 :
  public Mesh_3::Mesh_complex_3_in_triangulation_3_base<Tr>
{
  typedef Mesh_complex_3_in_triangulation_3<
    Tr,CornerIndex,CurveSegmentIndex>                             Self;
  typedef Mesh_3::Mesh_complex_3_in_triangulation_3_base<Tr>      Base;
  
public:
  typedef typename Base::size_type                        size_type;
  
  typedef typename Base::Edge                             Edge;
  typedef typename Base::Vertex_handle                    Vertex_handle;
  typedef CornerIndex                                     Corner_index;
  typedef CurveSegmentIndex                               Curve_segment_index;
  
  typedef typename Base::Triangulation                    Triangulation;
  
private:
  // Type to store the edges:
  //  - a set of std::pair<Vertex_handle,Vertex_handle> (ordered at insertion)
  //  - which allows fast lookup from one Vertex_handle
  //  - each element of the set has an associated info (Curve_segment_index) value
  typedef boost::bimaps::bimap< 
    boost::bimaps::multiset_of<Vertex_handle>,
    boost::bimaps::multiset_of<Vertex_handle>,
    boost::bimaps::set_of_relation<>,
    boost::bimaps::with_info<Curve_segment_index> >   Edge_map;

  typedef typename Edge_map::value_type               Internal_edge;
  
  // Type to store the corners
  typedef std::map<Vertex_handle,Corner_index>        Corner_map;
  
public:
  /**
   * Constructor
   */
  Mesh_complex_3_in_triangulation_3() 
    : Base()
    , edges_()
    , corners_() {}
  
  /**
   * Copy constructor
   */
  Mesh_complex_3_in_triangulation_3(const Self& rhs);
  
  /**
   * Destructor
   */
  virtual ~Mesh_complex_3_in_triangulation_3() {}
  
  /**
   * Assignement operator
   */
  Self& operator=(Self rhs)
  {
    swap(rhs);
    return *this;
  }
  
  /**
   * Swaps this & rhs
   */
  void swap(Self& rhs)
  {
    Base::swap(rhs);
    edges_.swap(rhs.edges_);
    corners_.swap(rhs.corners_);
  }
  
  /**
   * Clears data of c3t3
   */
  void clear()
  {
    Base::clear();
    edges_.clear();
    corners_.clear();
  }
  
  /// Import Base functions
  using Base::is_in_complex;
  using Base::add_to_complex;
  using Base::remove_from_complex;
  

  /**
   * Add edge e to complex, with Curve_segment_index index
   */  
  void add_to_complex(const Edge& e,
                      const Curve_segment_index& index)
  {
    add_to_complex(e.first->vertex(e.second),
                   e.first->vertex(e.third),
                   index);
  }
  
  /**
   * Add edge (v1,v2) to complex, with Curve_segment_index index
   */
  void add_to_complex(const Vertex_handle& v1,
                      const Vertex_handle& v2,
                      const Curve_segment_index& index)
  {
    add_to_complex(make_internal_edge(v1,v2), index);
  }
  
  /**
   * Mark vertex \c v as a corner of the complex
   */
  void add_to_complex(const Vertex_handle& v, const Corner_index& index)
  {
    v->set_dimension(0);
    corners_.insert(std::make_pair(v,index));
  }

  /**
   * Remove edge \c e from complex
   */  
  void remove_from_complex(const Edge& e)
  {
    remove_from_complex(e.first->vertex(e.second), e.first->vertex(e.third));
  }
  
  /**
   * Remove edge (v1,v2) from complex
   */
  void remove_from_complex(const Vertex_handle& v1, const Vertex_handle& v2)
  {
    remove_from_complex(make_internal_edge(v1,v2));
  }
  
  /**
   * Remove vertex \c v from complex
   */
  void remove_from_complex(const Vertex_handle& v)
  {
    corners_.erase(v);
    v->set_dimension(-1);
  }
  
  /**
   * Returns the number of edges of c3t3
   */
  size_type number_of_edges_in_complex() const
  {
    return edges_.size();
  }
  
  /**
   * Returns the number of corners of c3t3
   */
  size_type number_of_vertices_in_complex() const
  {
    return corners_.size();
  }
  
  /**
   * Returns true if edge \c e is in complex
   */
  bool is_in_complex(const Edge& e) const
  {
    return is_in_complex(e.first->vertex(e.second), e.first->vertex(e.third));
  }
  
  /**
   * Returns true if edge (v1,v2) is in C3T3
   */
  bool is_in_complex(const Vertex_handle& v1, const Vertex_handle& v2) const
  {
    return is_in_complex(make_internal_edge(v1,v2));
  }

  /**
   * Returns true if \c v is a 0-dimensionnal feature in the c3t3
   */
  bool is_in_complex(const Vertex_handle& v) const
  {
    return (corners_.find(v) != corners_.end());
  }
  
  /**
   * Returns Curve_segment_index of edge \c e
   */
  Curve_segment_index curve_segment_index(const Edge& e) const
  {
    return curve_segment_index(e.first->vertex(e.second),
                               e.first->vertex(e.third));
  }
  
  /**
   * Returns Curve_segment_index of edge \c (v1,v2)
   */
  Curve_segment_index curve_segment_index(const Vertex_handle& v1,
                                          const Vertex_handle& v2) const
  {
    return curve_index(make_internal_edge(v1,v2));
  }
  
  /**
   * Returns Corner_index of vertex \c v
   */
  Corner_index corner_index(const Vertex_handle& v) const
  {
    typename Corner_map::const_iterator it = corners_.find(v);
    if ( corners_.end() != it ) { return it->second; }
    return Corner_index();
  }
  
  /**
   * Fills \c out with incident edges (1-dimensional features of \c v.
   * OutputIterator value type is std::pair<Vertex_handle,Curve_segment_index>
   * \pre v->in_dimension() < 2 
   */
  template <typename OutputIterator>
  OutputIterator
  adjacent_vertices_in_complex(const Vertex_handle& v, OutputIterator out) const;
  
  // -----------------------------------
  // Undocumented
  // -----------------------------------
  
  /**
   * Returns true if c3t3 is valid
   */
  bool is_valid() const;
  
  // -----------------------------------
  // Complex traversal
  // -----------------------------------
private:
  class Edge_iterator_not_in_complex
  {
    const Self& c3t3_;
    const Curve_segment_index index_;
  public:
    Edge_iterator_not_in_complex(const Self& c3t3,
                                 const Curve_segment_index& index = Curve_segment_index())
    : c3t3_(c3t3)
    , index_(index) { }
    
    template <typename Iterator>
    bool operator()(Iterator it) const
    { 
      if ( index_ == Curve_segment_index() ) { return ! c3t3_.is_in_complex(*it); }
      else { return c3t3_.curve_segment_index(*it) != index_;  }
    }
  };
  
  class Vertex_iterator_not_in_complex
  {
    const Self& c3t3_;
    const Corner_index index_;
  public:
    Vertex_iterator_not_in_complex(const Self& c3t3,
                                   const Corner_index& index = Corner_index())
    : c3t3_(c3t3)
    , index_(index) { }
    
    template <typename ItMap>
    bool operator()(const ItMap it) const
    { 
      if ( index_ == Corner_index() ) { return false; }
      else { return it->second != index_;  }
    }
  };
  
  // Filtered iterator
  typedef Filter_iterator<
    typename Corner_map::const_iterator,
    Vertex_iterator_not_in_complex >            Vertex_map_filter_iterator;

  // Iterator type to get the first element of pair
  typedef boost::transform_iterator <
    Mesh_3::internal::First_of<typename Vertex_map_filter_iterator::value_type>,
    Vertex_map_filter_iterator >                Vertex_map_iterator_first;
  
  // Iterator type to remove a level of referencing
  class Vertex_map_iterator_first_dereference
    : public boost::iterator_adaptor <
        Vertex_map_iterator_first_dereference,
        Vertex_map_iterator_first,
        typename Vertex_map_iterator_first::value_type::value_type,
        boost::use_default,
        typename Vertex_map_iterator_first::value_type::reference >
  {
    typedef Vertex_map_iterator_first_dereference Self;
    typedef boost::iterator_adaptor <
        Vertex_map_iterator_first_dereference,
        Vertex_map_iterator_first,
        typename Vertex_map_iterator_first::value_type::value_type,
        boost::use_default,
        typename Vertex_map_iterator_first::value_type::reference > iterator_adaptor_;
  public:
    typedef typename  Vertex_map_iterator_first::reference  pointer;
    typedef typename iterator_adaptor_::reference           reference;
    
    Vertex_map_iterator_first_dereference() : Self::iterator_adaptor_() { }
    
    template < typename Iterator >
    Vertex_map_iterator_first_dereference(Iterator i)
      : Self::iterator_adaptor_(typename Self::iterator_adaptor_::base_type(i))
    { }
    
    pointer operator->() const { return *(this->base()); }
    reference operator*() const { return **(this->base()); }

    operator Vertex_handle() { return Vertex_handle(*(this->base())); }
  };
  
public:
  /// Iterator type to visit the edges of the 1D complex.
  typedef Filter_iterator<
    typename Triangulation::Finite_edges_iterator,
    Edge_iterator_not_in_complex >          Edges_in_complex_iterator;
  
  /// Returns a Facets_in_complex_iterator to the first facet of the 1D complex
  Edges_in_complex_iterator edges_in_complex_begin() const
  {
    return CGAL::filter_iterator(this->triangulation().finite_edges_end(),
                                 Edge_iterator_not_in_complex(*this),
                                 this->triangulation().finite_edges_begin());
  }
  
  /// Returns a Facets_in_complex_iterator to the first facet of the 1D complex
  Edges_in_complex_iterator
  edges_in_complex_begin(const Curve_segment_index& index) const
  {
    return CGAL::filter_iterator(this->triangulation().finite_edges_end(),
                                 Edge_iterator_not_in_complex(*this,index),
                                 this->triangulation().finite_edges_begin());
  }
  
  /// Returns past-the-end iterator on facet of the 1D complex
  Edges_in_complex_iterator edges_in_complex_end() const
  {
    return CGAL::filter_iterator(this->triangulation().finite_edges_end(),
                                 Edge_iterator_not_in_complex(*this));
  }
  
  /// Iterator type to visit the edges of the 0D complex.
  typedef Vertex_map_iterator_first_dereference Vertices_in_complex_iterator;
    
  /// Returns a Vertices_in_complex_iterator to the first vertex of the 0D complex
  Vertices_in_complex_iterator vertices_in_complex_begin() const
  {
    return CGAL::filter_iterator(corners_.end(),
                                 Vertex_iterator_not_in_complex(*this),
                                 corners_.begin());
  }

  /// Returns a Vertices_in_complex_iterator to the first vertex of the 0D complex
  Vertices_in_complex_iterator
  vertices_in_complex_begin(const Corner_index& index) const
  {
    return CGAL::filter_iterator(corners_.end(),
                                 Vertex_iterator_not_in_complex(*this,index),
                                 corners_.begin());
  }  
  
  /// Returns past-the-end iterator on facet of the 0D complex
  Vertices_in_complex_iterator vertices_in_complex_end() const
  {
    return CGAL::filter_iterator(corners_.end(),
                                 Vertex_iterator_not_in_complex(*this));
  }  
  
  
private:
  /**
   * Creates an Internal_edge object (i.e a pair of ordered Vertex_handle)
   */ 
  Internal_edge make_internal_edge(const Vertex_handle& v1,
                                   const Vertex_handle& v2) const
  {
    if ( v1 < v2 ) { return Internal_edge(v1,v2); }
    else { return Internal_edge(v2,v1); }
  }

  /**
   * Returns true if \c edge is in C3T3
   */
  bool is_in_complex(const Internal_edge& edge) const
  {
    return (curve_index(edge) != Curve_segment_index() );
  }
  
  /**
   * Add edge \c edge to complex, with Curve_segment_index index
   */
  void add_to_complex(const Internal_edge& edge, const Curve_segment_index& index)
  {
    CGAL_precondition(!is_in_complex(edge));
    std::pair<typename Edge_map::iterator, bool> it = edges_.insert(edge);
    it.first->info = index;
  }
  
  /**
   * Remove edge \c edge from complex
   */
  void remove_from_complex(const Internal_edge& edge)
  {
    edges_.erase(edge);
  }

  /**
   * Returns Curve_segment_index of edge \c edge
   */
  Curve_segment_index curve_index(const Internal_edge& edge) const
  {
    typename Edge_map::const_iterator it = edges_.find(edge);
    if ( edges_.end() != it ) { return it->info; }
    return Curve_segment_index();
  }
    
private:
  Edge_map edges_;
  Corner_map corners_;
};


template <typename Tr, typename CI_, typename CSI_>
Mesh_complex_3_in_triangulation_3<Tr,CI_,CSI_>::
Mesh_complex_3_in_triangulation_3(const Self& rhs)
  : Base(rhs)
  , edges_()
  , corners_()
{
  // Copy edges
  for ( typename Edge_map::const_iterator it = rhs.edges_.begin(), 
       end = rhs.edges_.end() ; it != end ; ++it )
  {
    const Vertex_handle& va = it->right;
    const Vertex_handle& vb = it->left;
    
    Vertex_handle new_va;
    this->triangulation().is_vertex(va->point(), new_va);
    
    Vertex_handle new_vb;
    this->triangulation().is_vertex(vb->point(), new_vb);
    
    this->add_to_complex(make_internal_edge(new_va,new_vb), it->info);
  }
  
  // Copy corners
  for ( typename Corner_map::const_iterator it = rhs.corners_.begin(), 
       end = rhs.corners_.end() ; it != end ; ++it )
  {
    Vertex_handle new_v;
    this->triangulation().is_vertex(it->first->point(), new_v);
    this->add_to_complex(new_v, it->second);
  }
}


template <typename Tr, typename CI_, typename CSI_>
template <typename OutputIterator>
OutputIterator
Mesh_complex_3_in_triangulation_3<Tr,CI_,CSI_>::
adjacent_vertices_in_complex(const Vertex_handle& v, OutputIterator out) const
{
  CGAL_precondition(v->in_dimension() < 2);
  
  typedef typename Edge_map::right_const_iterator Rcit;
  typedef typename Edge_map::left_const_iterator Lcit;

  // Add edges containing v is on the left
  std::pair<Rcit,Rcit> range_right = edges_.right.equal_range(v);
  for ( Rcit rit = range_right.first ; rit != range_right.second ; ++rit )
  {
    *out++ = std::make_pair(rit->second, rit->info);
  }
  
  // Add edges containing v on the right
  std::pair<Lcit,Lcit> range_left = edges_.left.equal_range(v);
  for ( Lcit lit = range_left.first ; lit != range_left.second ; ++lit )
  {
    *out++ = std::make_pair(lit->second, lit->info);
  }
  
  return out;
}


template <typename Tr, typename CI_, typename CSI_>
bool
Mesh_complex_3_in_triangulation_3<Tr,CI_,CSI_>::
is_valid() const
{
  typedef typename Tr::Point::Point    Bare_point;
  typedef typename Tr::Point::Weight   Weight;
  typedef Weight FT;

  std::map<Vertex_handle, int> vertex_map;
  
  // Fill map counting neighbor number for each vertex of an edge
  for ( typename Edge_map::const_iterator it = edges_.begin(),
       end = edges_.end() ; it != end ; ++it )
  {
    const Vertex_handle& v1 = it->right;
    if ( vertex_map.find(v1) == vertex_map.end() ) { vertex_map[v1] = 1; }
    else { vertex_map[v1] += 1; }
    
    const Vertex_handle& v2 = it->left;
    if ( vertex_map.find(v2) == vertex_map.end() ) { vertex_map[v2] = 1; }
    else { vertex_map[v2] += 1; }
  }
  
  // Verify that each vertex has 2 neighbors if it's not a corner
  for ( typename std::map<Vertex_handle, int>::iterator vit = vertex_map.begin(),
       vend = vertex_map.end() ; vit != vend ; ++vit )
  {
    if ( vit->first->in_dimension() != 0 && vit->second != 2 )
    {
      return false;
    }
  }
  
  // Verify that balls of each edge intersect
  for ( typename Edge_map::const_iterator it = edges_.begin(),
       end = edges_.end() ; it != end ; ++it )
  {
    const Bare_point& p = it->right->point().point();
    const Bare_point& q = it->left->point().point();
    
    typedef typename Tr::Geom_traits::Sphere_3 Sphere_3;
    typename Tr::Geom_traits::Construct_sphere_3 sphere = 
      this->triangulation().geom_traits().construct_sphere_3_object();

    typename Tr::Geom_traits::Do_intersect_3 do_intersect = 
      this->triangulation().geom_traits().do_intersect_3_object();

    const FT& sq_rp = it->right->point().weight();
    const FT& sq_rq = it->left->point().weight();
    
    if ( ! do_intersect(sphere(p, sq_rp), sphere(q, sq_rq)) )
    {
      std::cerr << "Point p[" << p << "], dim=" << it->right->in_dimension() 
                << " and q[" << q << "], dim=" << it->left->in_dimension() 
                << " form an edge but do not intersect !\n";
      return false;
    }
  }
  
  return true;
}


template < class Tr, class CI_, class CSI_>
std::ostream & 
operator<< (std::ostream& os, 
            const Mesh_complex_3_in_triangulation_3<Tr,CI_,CSI_> &c3t3)
{
  // TODO: implement edge saving
  return os << static_cast<const Mesh_3::Mesh_complex_3_in_triangulation_3_base<Tr>&>(c3t3);
}


template < class Tr, class CI_, class CSI_>
std::istream & 
operator>> (std::istream& is, 
            Mesh_complex_3_in_triangulation_3<Tr,CI_,CSI_> &c3t3)
{
  // TODO: implement edge loading
  is >> static_cast<Mesh_3::Mesh_complex_3_in_triangulation_3_base<Tr>&>(c3t3);
  return is;
}

} //namespace CGAL

#endif // CGAL_MESH_COMPLEX_3_IN_TRIANGULATION_3_H
