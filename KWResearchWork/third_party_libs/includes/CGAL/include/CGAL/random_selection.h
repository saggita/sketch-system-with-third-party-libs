// Copyright (c) 1997  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Generator/include/CGAL/random_selection.h $
// $Id: random_selection.h 58544 2010-09-08 09:16:31Z afabri $
// 
//
// Author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>

#ifndef CGAL_RANDOM_SELECTION_H
#define CGAL_RANDOM_SELECTION_H 1

#include <cstddef>
#include <iterator>
#include <CGAL/Random.h>

namespace CGAL {

template <class RandomAccessIterator, class Size, class OutputIterator,
          class Random>
OutputIterator random_selection( RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 Size n,
                                 OutputIterator result,
                                 Random& rnd)
    // choose a random item from the range [`first',`last') and write it
    // to `result', each item from the range with equal probability.
    // Repeat this n times, thus writing n items to `result'. A single
    // random number is needed from `rnd' for each item. Returns the
    // value of `result' after inserting the n items.
{
    std::ptrdiff_t m = last - first;
    for ( Size i = 0; i < n; i++) {
        *result++ = first[ rnd(m)];
    }
    return result;
}

template <class RandomAccessIterator, class Size, class OutputIterator>
OutputIterator random_selection( RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 Size n,
                                 OutputIterator result)
{
    return random_selection( first, last, n, result, default_random);
}

} //namespace CGAL    

#endif // CGAL_RANDOM_SELECTION_H //
