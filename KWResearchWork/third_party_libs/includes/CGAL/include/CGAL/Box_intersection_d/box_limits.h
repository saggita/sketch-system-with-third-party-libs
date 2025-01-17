// Copyright (c) 2004  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Box_intersection_d/include/CGAL/Box_intersection_d/box_limits.h $
// $Id: box_limits.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>
//                 Andreas Meyer <ameyer@mpi-sb.mpg.de>

#ifndef CGAL_BOX_INTERSECTION_D_BOX_LIMITS_H
#define CGAL_BOX_INTERSECTION_D_BOX_LIMITS_H

#include <CGAL/basic.h>
#include <limits>

namespace CGAL {

namespace Box_intersection_d {


template<class T>
struct box_limits {};

template<>
struct box_limits<int> {
    static int inf() { return (std::numeric_limits<int>::min)(); }
    static int sup() { return (std::numeric_limits<int>::max)(); }
};

template<>
struct box_limits<unsigned int> {
    static int inf() { return 0; }
    static int sup() { return (std::numeric_limits<unsigned int>::max)(); }
};

template<>
struct box_limits<float> {
    static float inf() { return -sup(); }
    static float sup() { return (std::numeric_limits<float>::max)(); }
};

template<>
struct box_limits<double> {
    static double inf() { return -sup(); }
    static double sup() { return (std::numeric_limits<double>::max)(); }
};

} // end namespace Box_intersection_d


} //namespace CGAL


#endif
