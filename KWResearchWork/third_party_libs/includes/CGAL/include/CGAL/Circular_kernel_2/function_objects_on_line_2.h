// Copyright (c) 2003-2008  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Circular_kernel_2/include/CGAL/Circular_kernel_2/function_objects_on_line_2.h $
// $Id: function_objects_on_line_2.h 46608 2008-10-31 17:08:32Z pmachado $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)


#ifndef CGAL_CIRCULAR_KERNEL_FUNCTION_OBJECTS_ON_LINE_2_H
#define CGAL_CIRCULAR_KERNEL_FUNCTION_OBJECTS_ON_LINE_2_H

#include <CGAL/Circular_kernel_2/internal_functions_on_line_2.h>
#include <CGAL/Circular_kernel_2/internal_functions_on_line_arc_2.h>

namespace CGAL {

namespace LinearFunctors {

  template < class CK >
  class Construct_line_2 : public  CK::Linear_kernel::Construct_line_2
  {
	  typedef typename CK::Line_arc_2            Line_arc_2;
    typedef typename CK::Line_2                Line_2;
    public:

    typedef typename CK::Linear_kernel::Construct_line_2::result_type 
      result_type;
    using CK::Linear_kernel::Construct_line_2::operator();

    result_type operator() (const Line_arc_2 & a) const
    {
      return (a.rep().supporting_line());
    }

    result_type
    operator() ( const typename CK::Polynomial_1_2 &eq )
      {
	      return construct_line_2<CK>(eq);
      }
  };

} // namespace LinearFunctors

} // namespace CGAL

#endif // CGAL_CIRCULAR_KERNEL_FUNCTION_OBJECTS_ON_LINE_2_H
