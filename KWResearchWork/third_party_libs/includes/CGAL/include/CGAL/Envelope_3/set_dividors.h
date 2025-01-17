// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Envelope_3/include/CGAL/Envelope_3/set_dividors.h $
// $Id: set_dividors.h 49630 2009-05-26 20:48:38Z ophirset $
// 
//
// Author(s)     : Michal Meyerovitch     <gorgymic@post.tau.ac.il>
//                 Baruch Zukerman        <baruchzu@post.tau.ac.il>

#ifndef CGAL_ENVELOPE_SET_DIVIDORS_H
#define CGAL_ENVELOPE_SET_DIVIDORS_H

#include <CGAL/Random.h>

namespace CGAL
{
namespace Envelope_3
{

//! All even-indexed elements are stored in the first sequence and all the 
//  odd-indexed are stored in the second sequence.
class Arbitrary_dividor
{
public:

  template <class InputIterator, class OutputIterator>
  void operator()(InputIterator begin, InputIterator end,
                  OutputIterator set1, OutputIterator set2)
  {
    bool set_first = true;
    for(; begin != end; ++begin, set_first = !set_first)
      if (set_first)
        *set1++ = *begin;
      else
        *set2++ = *begin;

  }
  
};

//! The last element is stored in the second sequence and all the other (n-1) 
//  elments are stored in the first sequence.
class Incremental_dividor
{
public:

  template <class InputIterator, class OutputIterator>
  void operator()(InputIterator begin, InputIterator end,
                  OutputIterator set1, OutputIterator set2)
  {
    std::size_t i, n = std::distance(begin, end);
    // all items but the last go to the first set
    for(i=0; i<(n-1); ++i, ++begin)
      *set1++ = *begin;
    // the last item goes to the second set
    *set2++ = *begin;
  }

};

//! The elements are divided exactly in the middle.
class Middle_dividor
{
public:

  template <class InputIterator, class OutputIterator>
  void operator()(InputIterator begin, InputIterator end,
                  OutputIterator set1, OutputIterator set2)
  {
    std::size_t i, n = std::distance(begin, end);

    for(i=0; i < n; ++i, ++begin)
    {
      if (i < n/2)
        *set1++ = *begin;
      else
        *set2++ = *begin;
    }
  }

};

//! The elements are divided randomly
class Random_dividor
{
public:
  
  template <class InputIterator, class OutputIterator>
  void operator()(InputIterator begin, InputIterator end,
                  OutputIterator set1, OutputIterator set2)
  {
    while (begin != end)
    {
      
      if (CGAL::default_random.get_bool())
        *set1++ = *begin++;
      else
        *set2++ = *begin++;
    }
  }

};


} // namespace Envelope_3
} // namespace CGAL

#endif 
