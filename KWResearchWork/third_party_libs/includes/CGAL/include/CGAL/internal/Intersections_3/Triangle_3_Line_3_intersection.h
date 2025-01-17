// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Intersections_3/include/CGAL/internal/Intersections_3/Triangle_3_Line_3_intersection.h $
// $Id: Triangle_3_Line_3_intersection.h 57305 2010-07-02 15:06:05Z stayeb $
//
//
// Author(s)     : Stéphane Tayeb
//
// Note : This implementation is adapted from Triangle_3_Line_3_do_intersect.h.

#ifndef CGAL_INTERNAL_INTERSECTIONS_3_TRIANGLE_3_LINE_3_INTERSECTION_H
#define CGAL_INTERNAL_INTERSECTIONS_3_TRIANGLE_3_LINE_3_INTERSECTION_H

#include <CGAL/kernel_basic.h>
#include <CGAL/intersections.h>

namespace CGAL {
namespace internal {

template <class K>
typename K::Point_3
t3l3_intersection_coplanar_aux(const typename K::Line_3& l,
                               const typename K::Point_3& a,
                               const typename K::Point_3& b,
                               const K& k)
{
  // Returns the intersection point between line l and segment [a,b]
  //
  // preconditions:
  //   + l,a,b are coplanar

  typedef typename K::Point_3 Point_3;
  typedef typename K::Vector_3 Vector_3;
  typedef typename K::FT FT;

  typename K::Construct_vector_3 vector =
    k.construct_vector_3_object();

  typename K::Construct_cross_product_vector_3 cross_product =
    k.construct_cross_product_vector_3_object();

  typename K::Compute_scalar_product_3 scalar_product =
    k.compute_scalar_product_3_object();

  typename K::Compute_squared_length_3 sq_length =
    k.compute_squared_length_3_object();

  const Point_3& p = l.point();
  const Vector_3& v = l.to_vector();
  const Vector_3 ab = vector(a,b);
  const Vector_3 pa = vector(p,a);

  const Vector_3 pa_ab = cross_product(pa,ab);
  const Vector_3 v_ab = cross_product(v,ab);

  const FT t = scalar_product(pa_ab,v_ab) / sq_length(v_ab);

  return ( p + t*v );
}


template <class K>
Object
t3l3_intersection_coplanar_aux(const typename K::Point_3& a,
                               const typename K::Point_3& b,
                               const typename K::Point_3& c,
                               const typename K::Line_3& l,
                               const bool negative_side,
                               const K& k)
{
  // This function is designed to clip pq into the triangle abc.
  // Point configuration should be as follows
  //
  //     |
  //     |    +b
  //     |
  //  +c |       +a
  //     |
  //     | l
  //
  // We know that c is isolated on the negative side of pq

  typedef typename K::Point_3 Point_3;

  typename K::Construct_segment_3 segment =
    k.construct_segment_3_object();

  // Let's get the intersection points
  const Point_3 l_bc = t3l3_intersection_coplanar_aux(l,b,c,k);
  const Point_3 l_ca = t3l3_intersection_coplanar_aux(l,c,a,k);

  if ( negative_side )
    return make_object(segment(l_bc, l_ca));
  else
    return make_object(segment(l_ca, l_bc));
}


template <class K>
Object
intersection_coplanar(const typename K::Triangle_3 &t,
                      const typename K::Line_3  &l,
                      const K & k )
{
  CGAL_kernel_precondition( ! k.is_degenerate_3_object()(t) ) ;
  CGAL_kernel_precondition( ! k.is_degenerate_3_object()(l) ) ;

  typedef typename K::Point_3 Point_3;

  typename K::Construct_point_on_3 point_on =
    k.construct_point_on_3_object();

  typename K::Construct_vertex_3 vertex_on =
    k.construct_vertex_3_object();

  typename K::Coplanar_orientation_3 coplanar_orientation =
    k.coplanar_orientation_3_object();

  typename K::Construct_segment_3 segment =
    k.construct_segment_3_object();

  const Point_3 & p = point_on(l,0);
  const Point_3 & q = point_on(l,1);

  const Point_3 & A = vertex_on(t,0);
  const Point_3 & B = vertex_on(t,1);
  const Point_3 & C = vertex_on(t,2);

  int k0 = 0;
  int k1 = 1;
  int k2 = 2;

  // Determine the orientation of the triangle in the common plane
  if (coplanar_orientation(A,B,C) != POSITIVE)
  {
    // The triangle is not counterclockwise oriented
    // swap two vertices.
    std::swap(k1,k2);
  }

  const Point_3& a = vertex_on(t,k0);
  const Point_3& b = vertex_on(t,k1);
  const Point_3& c = vertex_on(t,k2);

  // Test whether the line intersects the triangle in the common plane
  const Orientation pqa = coplanar_orientation(p,q,a);
  const Orientation pqb = coplanar_orientation(p,q,b);
  const Orientation pqc = coplanar_orientation(p,q,c);

  switch ( pqa ) {
    // -----------------------------------
    // pqa POSITIVE
    // -----------------------------------
    case POSITIVE:
      switch ( pqb ) {
        case POSITIVE:
          switch ( pqc ) {
            case POSITIVE:
              // the triangle lies in the positive halfspace
              // defined by the segment's supporting line.
              return Object();
            case NEGATIVE:
              // c is isolated on the negative side
              return t3l3_intersection_coplanar_aux(a,b,c,l,true,k);
            case COLLINEAR:
              return make_object(c);
          }

        case NEGATIVE:
          if ( POSITIVE == pqc )
            // b is isolated on the negative side
            return t3l3_intersection_coplanar_aux(c,a,b,l,true,k);
          else
            // a is isolated on the positive side (here mb c could be use as
            // an endpoint instead of computing an intersection is some cases)
            return t3l3_intersection_coplanar_aux(b,c,a,l,false,k);

        case COLLINEAR:
          switch ( pqc ) {
            case POSITIVE:
              return make_object(b);
            case NEGATIVE:
              // a is isolated on the positive side (here mb b could be use as
              // an endpoint instead of computing an intersection)
              return t3l3_intersection_coplanar_aux(b,c,a,l,false,k);
            case COLLINEAR:
              // b,c,p,q are aligned, [p,q]&[b,c] have the same direction
              return make_object(segment(b,c));
          }

        default: // should not happen.
          CGAL_error();
          return Object();
      }

    // -----------------------------------
    // pqa NEGATIVE
    // -----------------------------------
    case NEGATIVE:
      switch ( pqb ) {
        case POSITIVE:
          if ( POSITIVE == pqc )
            // a is isolated on the negative side
            return t3l3_intersection_coplanar_aux(b,c,a,l,true,k);
          else
            // b is isolated on the positive side (here mb c could be use as
            // an endpoint instead of computing an intersection, in some cases)
            return t3l3_intersection_coplanar_aux(c,a,b,l,false,k);

        case NEGATIVE:
          switch ( pqc ) {
            case POSITIVE:
              // c is isolated on the positive side
              return t3l3_intersection_coplanar_aux(a,b,c,l,false,k);
            case NEGATIVE:
              // the triangle lies in the negative halfspace
              // defined by the segment's supporting line.
              return Object();
            case COLLINEAR:
              return make_object(c);
          }

        case COLLINEAR:
          switch ( pqc ) {
            case POSITIVE:
              // a is isolated on the negative side (here mb b could be use as
              // an endpoint instead of computing an intersection)
              return t3l3_intersection_coplanar_aux(b,c,a,l,true,k);
            case NEGATIVE:
                return make_object(b);
            case COLLINEAR:
              // b,c,p,q are aligned, [p,q]&[c,b] have the same direction
              return make_object(segment(c,b));
          }

        default: // should not happen.
          CGAL_error();
          return Object();
      }

    // -----------------------------------
    // pqa COLLINEAR
    // -----------------------------------
    case COLLINEAR:
      switch ( pqb ) {
        case POSITIVE:
          switch ( pqc ) {
            case POSITIVE:
              return make_object(a);
            case NEGATIVE:
              // b is isolated on the positive side (here mb a could be use as
              // an endpoint instead of computing an intersection)
              return t3l3_intersection_coplanar_aux(c,a,b,l,false,k);
            case COLLINEAR:
              // a,c,p,q are aligned, [p,q]&[c,a] have the same direction
              return make_object(segment(c,a));
          }

        case NEGATIVE:
          switch ( pqc ) {
            case POSITIVE:
              // b is isolated on the negative side (here mb a could be use as
              // an endpoint instead of computing an intersection)
              return t3l3_intersection_coplanar_aux(c,a,b,l,true,k);
            case NEGATIVE:
              return make_object(a);
            case COLLINEAR:
              // a,c,p,q are aligned, [p,q]&[a,c] have the same direction
              return make_object(segment(a,c));
          }

        case COLLINEAR:
          switch ( pqc ) {
            case POSITIVE:
              // a,b,p,q are aligned, [p,q]&[a,b] have the same direction
              return make_object(segment(a,b));
            case NEGATIVE:
              // a,b,p,q are aligned, [p,q]&[b,a] have the same direction
              return make_object(segment(b,a));
            case COLLINEAR:
              // case pqc == COLLINEAR is impossible since the triangle is
              // assumed to be non flat
              CGAL_error();
              return Object();
          }

        default: // should not happen.
          CGAL_error();
          return Object();
      }

    default:// should not happen.
      CGAL_error();
      return Object();
  }
}


template <class K>
inline
Object
t3l3_intersection_aux(const typename K::Triangle_3 &t,
                      const typename K::Line_3 &l,
                      const K& k)
{
  typename K::Intersect_3 intersection =
    k.intersect_3_object();

  Object obj = intersection(l,t.supporting_plane());

  // Intersection should be a point (because of orientation test done before)
  if ( obj.is<typename K::Line_3>() )
    return Object();
  else
    return obj;
}


template <class K>
Object
intersection(const typename K::Triangle_3 &t,
             const typename K::Line_3 &l,
             const K& k)
{
  CGAL_kernel_precondition( ! k.is_degenerate_3_object()(t) ) ;
  CGAL_kernel_precondition( ! k.is_degenerate_3_object()(l) ) ;

  typedef typename K::Point_3 Point_3;

  typename K::Construct_point_on_3 point_on =
    k.construct_point_on_3_object();

  typename K::Construct_vertex_3 vertex_on =
    k.construct_vertex_3_object();

  typename K::Orientation_3 orientation =
    k.orientation_3_object();

  const Point_3 & a = vertex_on(t,0);
  const Point_3 & b = vertex_on(t,1);
  const Point_3 & c = vertex_on(t,2);
  const Point_3 & p = point_on(l,0);
  const Point_3 & q = point_on(l,1);

  if ( ( orientation(a,b,c,p) != COPLANAR )
      || ( orientation(a,b,c,q) != COPLANAR ) )
  {
    const Orientation pqab = orientation(p,q,a,b);
    const Orientation pqbc = orientation(p,q,b,c);
    switch ( pqab ) {
      case POSITIVE:
        if ( pqbc != NEGATIVE && orientation(p,q,c,a) != NEGATIVE )
          return t3l3_intersection_aux(t,l,k);
        else
          return Object();

      case NEGATIVE:
        if ( pqbc != POSITIVE && orientation(p,q,c,a) != POSITIVE )
          return t3l3_intersection_aux(t,l,k);
        else
          return Object();

      case COPLANAR:
        switch ( pqbc ) {
          case POSITIVE:
            if ( orientation(p,q,c,a) != NEGATIVE )
              return t3l3_intersection_aux(t,l,k);
            else
              return Object();

          case NEGATIVE:
            if ( orientation(p,q,c,a) != POSITIVE )
              return t3l3_intersection_aux(t,l,k);
            else
              return Object();

          case COPLANAR: // pqa or pqb or pqc are collinear
            return t3l3_intersection_aux(t,l,k);

          default: // should not happen.
            CGAL_error();
            return Object();
        }

      default: // should not happen.
        CGAL_error();
        return Object();
    }
  }

  // Coplanar case
  return intersection_coplanar(t,l,k);
}

template <class K>
Object
intersection(const typename K::Line_3 &l,
             const typename K::Triangle_3 &t,
             const K& k)
{
  return internal::intersection(t,l,k);
}


} // end namespace internal

template <class K>
inline
Object
intersection(const Triangle_3<K> &t, const Line_3<K> &l)
{
  return typename K::Intersect_3()(t,l);
}

template <class K>
inline
Object
intersection(const Line_3<K> &l, const Triangle_3<K> &t)
{
  return typename K::Intersect_3()(t,l);
}

} // end namespace CGAL

#endif // CGAL_INTERNAL_INTERSECTIONS_3_TRIANGLE_3_LINE_3_INTERSECTION_H
