// Copyright (c) 2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Cartesian_kernel/include/CGAL/predicates/kernel_ftC3.h $
// $Id: kernel_ftC3.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Herve Bronnimann, Sylvain Pion

#ifndef CGAL_PREDICATES_KERNEL_FTC3_H
#define CGAL_PREDICATES_KERNEL_FTC3_H

#include <CGAL/predicates/sign_of_determinant.h>
#include <CGAL/predicates/kernel_ftC2.h>
#include <CGAL/constructions/kernel_ftC3.h>

namespace CGAL {

template < class FT >
inline
typename Equal_to<FT>::result_type
parallelC3(const FT &v1x, const FT &v1y, const FT &v1z,
           const FT &v2x, const FT &v2y, const FT &v2z)
{
  return CGAL_AND_3( sign_of_determinant(v1x, v2x, v1y, v2y) == ZERO ,
                     sign_of_determinant(v1x, v2x, v1z, v2z) == ZERO ,
                     sign_of_determinant(v1y, v2y, v1z, v2z) == ZERO );
}

template < class FT >
typename Equal_to<FT>::result_type
parallelC3(const FT &s1sx, const FT &s1sy, const FT &s1sz,
           const FT &s1tx, const FT &s1ty, const FT &s1tz,
           const FT &s2sx, const FT &s2sy, const FT &s2sz,
           const FT &s2tx, const FT &s2ty, const FT &s2tz)
{
  // NB : Could be made slightly more efficient by computing the z differences
  // only when they are needed.
  FT v1x = s1tx - s1sx;
  FT v1y = s1ty - s1sy;
  FT v1z = s1tz - s1sz;
  FT v2x = s2tx - s2sx;
  FT v2y = s2ty - s2sy;
  FT v2z = s2tz - s2sz;
  return parallelC3(v1x, v1y, v1z, v2x, v2y, v2z);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Compare<FT>::result_type
compare_lexicographically_xyzC3(const FT &px, const FT &py, const FT &pz,
                                const FT &qx, const FT &qy, const FT &qz)
{
  typedef typename Compare<FT>::result_type Cmp;
  Cmp c = CGAL_NTS compare(px, qx);
  if (c != EQUAL) return c;
  c = CGAL_NTS compare(py, qy);
  if (c != EQUAL) return c;
  return CGAL_NTS compare(pz, qz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
strict_dominanceC3(const FT &px, const FT &py, const FT &pz,
		   const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_AND_3( CGAL_NTS compare(px, qx) == LARGER ,
	             CGAL_NTS compare(py, qy) == LARGER ,
	             CGAL_NTS compare(pz, qz) == LARGER );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
dominanceC3(const FT &px, const FT &py, const FT &pz,
	    const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_AND_3( CGAL_NTS compare(px, qx) != SMALLER , 
	             CGAL_NTS compare(py, qy) != SMALLER ,
	             CGAL_NTS compare(pz, qz) != SMALLER );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
collinearC3(const FT &px, const FT &py, const FT &pz,
            const FT &qx, const FT &qy, const FT &qz,
            const FT &rx, const FT &ry, const FT &rz)
{
  FT dpx = px-rx;
  FT dqx = qx-rx;
  FT dpy = py-ry;
  FT dqy = qy-ry;
  if (sign_of_determinant(dpx, dqx, dpy, dqy) != ZERO)
      return false;
  FT dpz = pz-rz;
  FT dqz = qz-rz;
  return CGAL_AND( sign_of_determinant(dpx, dqx, dpz, dqz) == ZERO ,
                   sign_of_determinant(dpy, dqy, dpz, dqz) == ZERO );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Orientation, FT>::type
orientationC3(const FT &px, const FT &py, const FT &pz,
              const FT &qx, const FT &qy, const FT &qz,
              const FT &rx, const FT &ry, const FT &rz,
              const FT &sx, const FT &sy, const FT &sz)
{
  return sign_of_determinant<FT>(qx-px,rx-px,sx-px,
                                    qy-py,ry-py,sy-py,
                                    qz-pz,rz-pz,sz-pz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Orientation, FT>::type
orientationC3(const FT &ux, const FT &uy, const FT &uz,
              const FT &vx, const FT &vy, const FT &vz,
              const FT &wx, const FT &wy, const FT &wz)
{
  return sign_of_determinant(ux, vx, wx,
                                uy, vy, wy,
                                uz, vz, wz);
}

template < class FT >
inline
typename Same_uncertainty_nt<Angle, FT>::type
angleC3(const FT &px, const FT &py, const FT &pz,
        const FT &qx, const FT &qy, const FT &qz,
        const FT &rx, const FT &ry, const FT &rz)
{
  return enum_cast<Angle>(CGAL_NTS sign((px-qx)*(rx-qx)+
	                                (py-qy)*(ry-qy)+
				        (pz-qz)*(rz-qz)));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Orientation, FT>::type
coplanar_orientationC3(const FT &px, const FT &py, const FT &pz,
                       const FT &qx, const FT &qy, const FT &qz,
                       const FT &rx, const FT &ry, const FT &rz,
                       const FT &sx, const FT &sy, const FT &sz)
{
  typedef typename Same_uncertainty_nt<Orientation, FT>::type  Ori;
  Ori oxy_pqr = orientationC2(px,py,qx,qy,rx,ry);
  if (oxy_pqr != COLLINEAR)
      return oxy_pqr * orientationC2(px,py,qx,qy,sx,sy);

  Ori oyz_pqr = orientationC2(py,pz,qy,qz,ry,rz);
  if (oyz_pqr != COLLINEAR)
      return oyz_pqr * orientationC2(py,pz,qy,qz,sy,sz);

  Ori oxz_pqr = orientationC2(px,pz,qx,qz,rx,rz);
  CGAL_kernel_assertion(oxz_pqr != COLLINEAR);
  return oxz_pqr * orientationC2(px,pz,qx,qz,sx,sz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Orientation, FT>::type
coplanar_orientationC3(const FT &px, const FT &py, const FT &pz,
                       const FT &qx, const FT &qy, const FT &qz,
                       const FT &rx, const FT &ry, const FT &rz)
{
  typedef typename Same_uncertainty_nt<Orientation, FT>::type  Ori;
  Ori oxy_pqr = orientationC2(px,py,qx,qy,rx,ry);
  if (oxy_pqr != COLLINEAR)
      return oxy_pqr;

  Ori oyz_pqr = orientationC2(py,pz,qy,qz,ry,rz);
  if (oyz_pqr != COLLINEAR)
      return oyz_pqr;

  return orientationC2(px,pz,qx,qz,rx,rz);
}

template < class FT >
CGAL_KERNEL_LARGE_INLINE
typename Same_uncertainty_nt<Bounded_side, FT>::type
coplanar_side_of_bounded_circleC3(const FT &px, const FT &py, const FT &pz,
                                  const FT &qx, const FT &qy, const FT &qz,
                                  const FT &rx, const FT &ry, const FT &rz,
                                  const FT &tx, const FT &ty, const FT &tz)
{
  // The approach is to compute side_of_bounded_sphere(p,q,r,t+v,t),
  // with v = pq ^ pr.
  // Note : since the circle defines the orientation of the plane, it can not
  // be considered oriented.
  FT ptx = px - tx;
  FT pty = py - ty;
  FT ptz = pz - tz;
  FT pt2 = CGAL_NTS square(ptx) + CGAL_NTS square(pty) + CGAL_NTS square(ptz);
  FT qtx = qx - tx;
  FT qty = qy - ty;
  FT qtz = qz - tz;
  FT qt2 = CGAL_NTS square(qtx) + CGAL_NTS square(qty) + CGAL_NTS square(qtz);
  FT rtx = rx - tx;
  FT rty = ry - ty;
  FT rtz = rz - tz;
  FT rt2 = CGAL_NTS square(rtx) + CGAL_NTS square(rty) + CGAL_NTS square(rtz);
  FT pqx = qx - px;
  FT pqy = qy - py;
  FT pqz = qz - pz;
  FT prx = rx - px;
  FT pry = ry - py;
  FT prz = rz - pz;
  FT vx = pqy*prz - pqz*pry;
  FT vy = pqz*prx - pqx*prz;
  FT vz = pqx*pry - pqy*prx;
  FT v2 = CGAL_NTS square(vx) + CGAL_NTS square(vy) + CGAL_NTS square(vz);
  return enum_cast<Bounded_side>(sign_of_determinant(ptx,pty,ptz,pt2,
                                                        rtx,rty,rtz,rt2,
                                                        qtx,qty,qtz,qt2,
                                                        vx,vy,vz,v2));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
collinear_are_ordered_along_lineC3(
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz,
     const FT &rx, const FT &ry, const FT &rz)
{
  if (px < qx) return !(rx < qx);
  if (qx < px) return !(qx < rx);
  if (py < qy) return !(ry < qy);
  if (qy < py) return !(qy < ry);
  if (pz < qz) return !(rz < qz);
  if (qz < pz) return !(qz < rz);
  return true; // p==q
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
collinear_are_strictly_ordered_along_lineC3(
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz,
     const FT &rx, const FT &ry, const FT &rz)
{
  if (px < qx) return (qx < rx);
  if (qx < px) return (rx < qx);
  if (py < qy) return (qy < ry);
  if (qy < py) return (ry < qy);
  if (pz < qz) return (qz < rz);
  if (qz < pz) return (rz < qz);
  return false; // p==q
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
equal_directionC3(const FT &dx1, const FT &dy1, const FT &dz1,
                  const FT &dx2, const FT &dy2, const FT &dz2)
{
  return sign_of_determinant(dx1, dy1, dx2, dy2) == ZERO
      && sign_of_determinant(dx1, dz1, dx2, dz2) == ZERO
      && sign_of_determinant(dy1, dz1, dy2, dz2) == ZERO
      && CGAL_NTS sign(dx1) == CGAL_NTS sign(dx2)
      && CGAL_NTS sign(dy1) == CGAL_NTS sign(dy2)
      && CGAL_NTS sign(dz1) == CGAL_NTS sign(dz2);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
equal_planeC3(const FT &ha, const FT &hb, const FT &hc, const FT &hd,
              const FT &pa, const FT &pb, const FT &pc, const FT &pd)
{
    typedef typename Sgn<FT>::result_type  Sg;

    if (!equal_directionC3(ha, hb, hc, pa, pb, pc))
	return false; // Not parallel.

    Sg s1a = CGAL_NTS sign(ha);
    if (s1a != ZERO)
        return CGAL_AND( s1a == CGAL_NTS sign(pa) ,
                         sign_of_determinant(pa, pd, ha, hd) == ZERO );
    Sg s1b = CGAL_NTS sign(hb);
    if (s1b != ZERO)
        return s1b == CGAL_NTS sign(pb)
            && sign_of_determinant(pb, pd, hb, hd) == ZERO;
    return CGAL_NTS sign(pc) == CGAL_NTS sign(hc)
        && sign_of_determinant(pc, pd, hc, hd) == ZERO;
}

template <class FT >
CGAL_KERNEL_LARGE_INLINE
typename Same_uncertainty_nt<Oriented_side, FT>::type
side_of_oriented_planeC3(const FT &a,  const FT &b,  const FT &c, const FT &d,
                         const FT &px, const FT &py, const FT &pz)
{
  return CGAL_NTS sign(a*px + b*py + c*pz + d);
}

template <class FT >
CGAL_KERNEL_LARGE_INLINE
typename Same_uncertainty_nt<Oriented_side, FT>::type
side_of_oriented_sphereC3(const FT &px, const FT &py, const FT &pz,
                          const FT &qx, const FT &qy, const FT &qz,
                          const FT &rx, const FT &ry, const FT &rz,
                          const FT &sx, const FT &sy, const FT &sz,
                          const FT &tx, const FT &ty, const FT &tz)
{
  FT ptx = px - tx;
  FT pty = py - ty;
  FT ptz = pz - tz;
  FT pt2 = CGAL_NTS square(ptx) + CGAL_NTS square(pty) + CGAL_NTS square(ptz);
  FT qtx = qx - tx;
  FT qty = qy - ty;
  FT qtz = qz - tz;
  FT qt2 = CGAL_NTS square(qtx) + CGAL_NTS square(qty) + CGAL_NTS square(qtz);
  FT rtx = rx - tx;
  FT rty = ry - ty;
  FT rtz = rz - tz;
  FT rt2 = CGAL_NTS square(rtx) + CGAL_NTS square(rty) + CGAL_NTS square(rtz);
  FT stx = sx - tx;
  FT sty = sy - ty;
  FT stz = sz - tz;
  FT st2 = CGAL_NTS square(stx) + CGAL_NTS square(sty) + CGAL_NTS square(stz);
  return sign_of_determinant(ptx,pty,ptz,pt2,
                                rtx,rty,rtz,rt2,
                                qtx,qty,qtz,qt2,
                                stx,sty,stz,st2);
  // Note that the determinant above is det(P,R,Q,S) (Q and R are swapped)!
}

template <class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Bounded_side, FT>::type
side_of_bounded_sphereC3(const FT &px, const FT &py, const FT &pz,
                         const FT &qx, const FT &qy, const FT &qz,
                         const FT &rx, const FT &ry, const FT &rz,
                         const FT &sx, const FT &sy, const FT &sz,
                         const FT &tx, const FT &ty, const FT &tz)
{
  return enum_cast<Bounded_side>( side_of_oriented_sphereC3(px, py, pz,
                                                            qx, qy, qz,
                                                            rx, ry, rz,
                                                            sx, sy, sz,
                                                            tx, ty, tz)
                                * orientationC3(px, py, pz,
                                                qx, qy, qz,
                                                rx, ry, rz,
                                                sx, sy, sz) );
}

template <class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Bounded_side, FT>::type
side_of_bounded_sphereC3(const FT &px, const FT &py, const FT &pz,
                         const FT &qx, const FT &qy, const FT &qz,
                         const FT &tx, const FT &ty, const FT &tz)
{
  // Returns whether T lies inside or outside the sphere which diameter is PQ.
  return enum_cast<Bounded_side>( CGAL_NTS sign((tx-px)*(qx-tx)
	                                      + (ty-py)*(qy-ty)
	                                      + (tz-pz)*(qz-tz)) );
}

template < class FT >
CGAL_KERNEL_INLINE
typename Compare<FT>::result_type
cmp_dist_to_pointC3(const FT &px, const FT &py, const FT &pz,
                    const FT &qx, const FT &qy, const FT &qz,
                    const FT &rx, const FT &ry, const FT &rz)
{
  return CGAL_NTS compare(squared_distanceC3(px,py,pz,qx,qy,qz),
                          squared_distanceC3(px,py,pz,rx,ry,rz));
}

// Because of the way the filtered predicates generator script works,
// cmp_dist_to_pointC3() must be defined _before_ ths following one.
template <class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Same_uncertainty_nt<Bounded_side, FT>::type
side_of_bounded_sphereC3(const FT &px, const FT &py, const FT &pz,
                         const FT &qx, const FT &qy, const FT &qz,
                         const FT &sx, const FT &sy, const FT &sz,
                         const FT &tx, const FT &ty, const FT &tz)
{
  // Returns whether T lies inside or outside the sphere which equatorial
  // circle is PQR.

  // This code is inspired by the one of circumcenterC3(3 points).

  FT psx = px-sx;
  FT psy = py-sy;
  FT psz = pz-sz;
  FT ps2 = CGAL_NTS square(psx) + CGAL_NTS square(psy) + CGAL_NTS square(psz);
  FT qsx = qx-sx;
  FT qsy = qy-sy;
  FT qsz = qz-sz;
  FT qs2 = CGAL_NTS square(qsx) + CGAL_NTS square(qsy) + CGAL_NTS square(qsz);
  FT rsx = psy*qsz-psz*qsy;
  FT rsy = psz*qsx-psx*qsz;
  FT rsz = psx*qsy-psy*qsx;
  FT tsx = tx-sx;
  FT tsy = ty-sy;
  FT tsz = tz-sz;

  FT num_x = ps2 * determinant(qsy,qsz,rsy,rsz)
	   - qs2 * determinant(psy,psz,rsy,rsz);
  FT num_y = ps2 * determinant(qsx,qsz,rsx,rsz)
	   - qs2 * determinant(psx,psz,rsx,rsz);
  FT num_z = ps2 * determinant(qsx,qsy,rsx,rsy)
	   - qs2 * determinant(psx,psy,rsx,rsy);

  FT den2  = 2 * determinant(psx,psy,psz,
                                   qsx,qsy,qsz,
                                   rsx,rsy,rsz);

  // The following could be simplified a bit.
  return enum_cast<Bounded_side>(
                      cmp_dist_to_pointC3<FT>(num_x,    - num_y,  num_z,
	                                      psx*den2, psy*den2, psz*den2,
	                                      tsx*den2, tsy*den2, tsz*den2) );
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
has_larger_dist_to_pointC3(const FT &px, const FT &py, const FT &pz,
                           const FT &qx, const FT &qy, const FT &qz,
                           const FT &rx, const FT &ry, const FT &rz)
{
  return cmp_dist_to_pointC3(px,py,pz,qx,qy,qz,rx,ry,rz) == LARGER;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
has_smaller_dist_to_pointC3(const FT &px, const FT &py, const FT &pz,
                            const FT &qx, const FT &qy, const FT &qz,
                            const FT &rx, const FT &ry, const FT &rz)
{
  return cmp_dist_to_pointC3(px,py,pz,qx,qy,qz,rx,ry,rz) == SMALLER;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Compare<FT>::result_type
cmp_signed_dist_to_directionC3( const FT &pa, const FT &pb, const FT &pc,
                                const FT &px, const FT &py, const FT &pz,
                                const FT &qx, const FT &qy, const FT &qz)
{
  return CGAL_NTS compare(scaled_distance_to_directionC3(pa,pb,pc,px,py,pz),
                          scaled_distance_to_directionC3(pa,pb,pc,qx,qy,qz));
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
has_larger_signed_dist_to_directionC3(
     const FT &pa, const FT &pb, const FT &pc,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return cmp_signed_dist_to_directionC3(pa,pb,pc,px,py,pz,qx,qy,qz) == LARGER;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
has_smaller_signed_dist_to_directionC3(
     const FT &pa, const FT &pb, const FT &pc,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return cmp_signed_dist_to_directionC3(pa,pb,pc,px,py,pz,qx,qy,qz) == SMALLER;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Compare<FT>::result_type
cmp_signed_dist_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
  return sign_of_determinant<FT>( pqx-ppx, pqy-ppy, pqz-ppz,
	                             prx-ppx, pry-ppy, prz-ppz,
	                             px-qx,   py-qy,   pz-qz);
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
has_larger_signed_dist_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
    return cmp_signed_dist_to_planeC3(ppx, ppy, ppz, pqx, pqy, pqz,
	    prx, pry, prz, px, py, pz, qx, qy, qz) == LARGER;
}

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
typename Equal_to<FT>::result_type
has_smaller_signed_dist_to_planeC3(
     const FT &ppx, const FT &ppy, const FT &ppz,
     const FT &pqx, const FT &pqy, const FT &pqz,
     const FT &prx, const FT &pry, const FT &prz,
     const FT &px, const FT &py, const FT &pz,
     const FT &qx, const FT &qy, const FT &qz)
{
    return cmp_signed_dist_to_planeC3(ppx, ppy, ppz, pqx, pqy, pqz,
	    prx, pry, prz, px, py, pz, qx, qy, qz) == SMALLER;
}

} //namespace CGAL

#endif // CGAL_PREDICATES_KERNEL_FTC3_H
