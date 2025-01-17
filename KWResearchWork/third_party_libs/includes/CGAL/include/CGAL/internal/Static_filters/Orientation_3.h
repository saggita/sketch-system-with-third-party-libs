// Copyright (c) 2001,2004  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Filtered_kernel/include/CGAL/internal/Static_filters/Orientation_3.h $
// $Id: Orientation_3.h 61261 2011-02-16 15:51:53Z afabri $
// 
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_INTERNAL_STATIC_FILTERS_ORIENTATION_3_H
#define CGAL_INTERNAL_STATIC_FILTERS_ORIENTATION_3_H

#include <CGAL/Profile_counter.h>
#include <CGAL/internal/Static_filters/Static_filter_error.h>
#include <CGAL/internal/Static_filters/tools.h>
#include <cmath>

namespace CGAL { namespace internal { namespace Static_filters_predicates {

template < typename K_base >
class Orientation_3
  : public K_base::Orientation_3
{
  typedef typename K_base::Point_3          Point_3;
  typedef typename K_base::Vector_3         Vector_3;
  typedef typename K_base::Sphere_3         Sphere_3;
  typedef typename K_base::Tetrahedron_3    Tetrahedron_3;
  typedef typename K_base::Orientation_3    Base;

public:
 typedef typename Base::result_type  result_type;

#ifndef CGAL_CFG_MATCHING_BUG_6
  using Base::operator();
#else 
  result_type
  operator()(const Vector_3& u, const Vector_3& v, const Vector_3& w) const
  { 
    return Base::operator()(u,v,w);
  }  

  result_type
  operator()(const Sphere_3& s) const
  { 
    return Base::operator()(s);
  }

  result_type
  operator()(const Tetrahedron_3& t) const
  { 
    return Base::operator()(t);
  }
#endif

  result_type 
  operator()(const Point_3 &p, const Point_3 &q,
	     const Point_3 &r, const Point_3 &s) const
  {
      CGAL_BRANCH_PROFILER_3("semi-static failures/attempts/calls to   : Orientation_3", tmp);

      Get_approx<Point_3> get_approx; // Identity functor for all points
                                      // but lazy points.

      double px, py, pz, qx, qy, qz, rx, ry, rz, sx, sy, sz;

      if (fit_in_double(get_approx(p).x(), px) && fit_in_double(get_approx(p).y(), py) &&
          fit_in_double(get_approx(p).z(), pz) &&
          fit_in_double(get_approx(q).x(), qx) && fit_in_double(get_approx(q).y(), qy) &&
          fit_in_double(get_approx(q).z(), qz) &&
          fit_in_double(get_approx(r).x(), rx) && fit_in_double(get_approx(r).y(), ry) &&
          fit_in_double(get_approx(r).z(), rz) &&
          fit_in_double(get_approx(s).x(), sx) && fit_in_double(get_approx(s).y(), sy) &&
          fit_in_double(get_approx(s).z(), sz))
      {
	  CGAL_BRANCH_PROFILER_BRANCH_1(tmp);

          double pqx = qx - px;
          double pqy = qy - py;
          double pqz = qz - pz;
          double prx = rx - px;
          double pry = ry - py;
          double prz = rz - pz;
          double psx = sx - px;
          double psy = sy - py;
          double psz = sz - pz;

          // CGAL::abs uses fabs on platforms where it is faster than (a<0)?-a:a
          // Then semi-static filter.
          double maxx = CGAL::abs(pqx);
          double maxy = CGAL::abs(pqy);
          double maxz = CGAL::abs(pqz);

          double aprx = CGAL::abs(prx);
          double apsx = CGAL::abs(psx);

          double apry = CGAL::abs(pry);
          double apsy = CGAL::abs(psy);

          double aprz = CGAL::abs(prz);
          double apsz = CGAL::abs(psz);

          if (maxx < aprx) maxx = aprx;
          if (maxx < apsx) maxx = apsx;
          if (maxy < apry) maxy = apry;
          if (maxy < apsy) maxy = apsy;
          if (maxz < aprz) maxz = aprz;
          if (maxz < apsz) maxz = apsz;

          double det = CGAL::determinant(pqx, pqy, pqz,
                                         prx, pry, prz,
                                         psx, psy, psz);

          // Sort maxx < maxy < maxz.
          if (maxx > maxz)
              std::swap(maxx, maxz);
          if (maxy > maxz)
              std::swap(maxy, maxz);
          else if (maxy < maxx)
              std::swap(maxx, maxy);

          // Protect against underflow in the computation of eps.
          if (maxx < 1e-97) /* cbrt(min_double/eps) */ {
            if (maxx == 0)
              return ZERO;
          }
          // Protect against overflow in the computation of det.
          else if (maxz < 1e102) /* cbrt(max_double [hadamard]/4) */ {
            double eps = 5.1107127829973299e-15 * maxx * maxy * maxz;
            if (det > eps)  return POSITIVE;
            if (det < -eps) return NEGATIVE;
          }

	  CGAL_BRANCH_PROFILER_BRANCH_2(tmp);
      }

      return Base::operator()(p, q, r, s);
  }

  // Computes the epsilon for Orientation_3.
  static double compute_epsilon()
  {
    typedef Static_filter_error F;
    F t1 = F(1, F::ulp()/2);         // First translation
    F det = CGAL::determinant(t1, t1, t1,
                              t1, t1, t1,
                              t1, t1, t1); // Full det
    double err = det.error();
    err += err * 2 * F::ulp(); // Correction due to "eps * maxx * maxy...".
    std::cerr << "*** epsilon for Orientation_3 = " << err << std::endl;
    return err;
  }

};

} } } // namespace CGAL::internal::Static_filters_predicates

#endif // CGAL_INTERNAL_STATIC_FILTERS_ORIENTATION_3_H
