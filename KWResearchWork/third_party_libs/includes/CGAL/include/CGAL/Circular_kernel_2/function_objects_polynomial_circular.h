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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Circular_kernel_2/include/CGAL/Circular_kernel_2/function_objects_polynomial_circular.h $
// $Id: function_objects_polynomial_circular.h 57902 2010-08-10 08:02:28Z afabri $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_CIRCULAR_KERNEL_FUNCTION_OBJECTS_POLYNOMIAL_CIRCULAR_H
#define CGAL_CIRCULAR_KERNEL_FUNCTION_OBJECTS_POLYNOMIAL_CIRCULAR_H

#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/Circular_kernel_2/internal_functions_on_circular_arc_2.h>
#include <CGAL/Circular_kernel_2/internal_functions_on_line_arc_2.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Object.h>

namespace CGAL {
namespace CircularFunctors {


  template < class CK >
  class Compare_x_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Compare_x_2
#endif
  {
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Point_2 Point_2;

  public:

    typedef typename CK::Linear_kernel::Compare_x_2::result_type result_type;
#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Compare_x_2::operator();
#else
    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Compare_x_2 LK_Compare_x_2;
    typedef typename CK::Line_2 Line_2;

    result_type
    operator() (const Point_2 &p0,
                const Point_2 &p1) const
    {
      return LK_Compare_x_2()(p0, p1);
    }

    result_type
    operator() (const Point_2 &p0,
                const Line_2 &p1,
                const Line_2 &p2) const
    {
      return LK_Compare_x_2()(p0, p1,p2);
    }

    result_type
    operator() (const Line_2 &p0,
                const Line_2 &p1,
                const Line_2 &p2) const
    {
      return LK_Compare_x_2()(p0, p1,p2);
    }

    result_type
    operator() (const Line_2 &p0,
                const Line_2 &p1,
                const Line_2 &p2,
                const Line_2 &p3) const
    {
      return LK_Compare_x_2()(p0, p1,p2,p3);
    }
#endif

    result_type
    operator() (const Circular_arc_point_2 &p0,
                const Circular_arc_point_2 &p1) const
    { return CircularFunctors::compare_x<CK>(p0, p1);}

  };


  template < class CK >
  class Compare_y_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Compare_y_2
#endif
  {
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Point_2 Point_2;

  public:
	
    typedef typename CK::Linear_kernel::Compare_y_2::result_type result_type;
#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Compare_y_2::operator();
#else

    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Compare_y_2 LK_Compare_y_2;
    typedef typename CK::Line_2 Line_2;

    result_type
    operator() (const Point_2 &p0,
                const Point_2 &p1) const
    {
      return LK_Compare_y_2()(p0, p1);
    }

    result_type
    operator() (const Point_2 &p0,
                const Line_2 &p1,
                const Line_2 &p2) const
    {
      return LK_Compare_y_2()(p0, p1,p2);
    }

    result_type
    operator() (const Line_2 &p0,
                const Line_2 &p1,
                const Line_2 &p2) const
    {
      return LK_Compare_y_2()(p0, p1,p2);
    }

    result_type
    operator() (const Line_2 &p0,
                const Line_2 &p1,
                const Line_2 &p2,
                const Line_2 &p3) const
    {
      return LK_Compare_y_2()(p0, p1,p2,p3);
    }
#endif

    result_type
    operator() (const Circular_arc_point_2 &p0,
                const Circular_arc_point_2 &p1) const
    {return CircularFunctors::compare_y<CK>(p0, p1);}

  };

  template < class CK >
  class Compare_xy_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Compare_xy_2
#endif
  {
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Point_2 Point_2;
    
  public:

    typedef typename CK::Linear_kernel::Compare_xy_2::result_type result_type;
#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Compare_xy_2::operator();
#else 

    result_type
    operator() (const Point_2 &p0,
                const Point_2 &p1) const
    {
      typedef typename CK::Linear_kernel LK;
      typedef typename LK::Compare_xy_2 LK_Compare_xy_2;
      return LK_Compare_xy_2()(p0, p1);
    }
#endif

    result_type
    operator() (const Circular_arc_point_2 &p0,
                const Circular_arc_point_2 &p1) const
    { return CircularFunctors::compare_xy<CK>(p0, p1);}

  };

  template < class CK >
  class In_x_range_2
  {
    typedef typename CK::Circular_arc_2          Circular_arc_2;
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Line_arc_2              Line_arc_2;

  public:
    typedef bool         result_type;
    
    result_type
    operator()(const Circular_arc_2 &a, const Circular_arc_point_2 &p) const
    { return CircularFunctors::point_in_x_range<CK>(a, p); }

    result_type
    operator()(const Line_arc_2 &a, const Circular_arc_point_2 &p) const
    { return CircularFunctors::point_in_x_range<CK>(a, p); }
    
  };

  
  template < class CK >
  class Has_on_2
    : public CK::Linear_kernel::Has_on_2
  {
    typedef typename CK::Circular_arc_2          Circular_arc_2;
    typedef typename CK::Circular_arc_point_2    Circular_arc_point_2;
    typedef typename CK::Line_arc_2              Line_arc_2;
    typedef typename CK::Circle_2                Circle_2;
    typedef typename CK::Line_2                  Line_2;

  public:
	  typedef typename CK::Linear_kernel::Has_on_2::result_type result_type;
    
    using CK::Linear_kernel::Has_on_2::operator();

    result_type
    operator()(const Circle_2 &a, const Circular_arc_point_2 &p) const
    { return CircularFunctors::has_on<CK>(a, p); }
    
    result_type
    operator()(const Line_2 &a, const Circular_arc_point_2 &p) const
    { return LinearFunctors::has_on<CK>(a, p); }
    
    result_type
    operator()(const Circular_arc_2 &a, const Circular_arc_point_2 &p) const
    { return CircularFunctors::has_on<CK>(a, p); }

    result_type
    operator()(const Line_arc_2 &a, const Circular_arc_point_2 &p) const
    { return CircularFunctors::has_on<CK>(a, p); }
    
  };
  
  template < class CK >
  class Compare_y_to_right_2
  {
    typedef typename CK::Circular_arc_2           Circular_arc_2;
    typedef typename CK::Circular_arc_point_2  Circular_arc_point_2;
    typedef typename CK::Line_arc_2               Line_arc_2;

  public:
    typedef CGAL::Comparison_result result_type;
    
    result_type
    operator()(const Circular_arc_2 &a1,
               const Circular_arc_2 &a2,
               const Circular_arc_point_2 &p) const
    { return CircularFunctors::compare_y_to_right<CK>(a1, a2, p); }

    result_type
    operator()(const Line_arc_2 &a1,
               const Line_arc_2 &a2,
               const Circular_arc_point_2 &p) const
    { return CircularFunctors::compare_y_to_right<CK>(a1, a2, p); }

    result_type
    operator()(const Line_arc_2 &a1,
               const Circular_arc_2 &a2,
               const Circular_arc_point_2 &p) const
    { return CircularFunctors::compare_y_to_right<CK>(a1, a2, p); }

    result_type
    operator()(const Circular_arc_2 &a1,
               const Line_arc_2 &a2,
               const Circular_arc_point_2 &p) const
    { if (CircularFunctors::compare_y_to_right<CK>(a2, a1, p) == CGAL::LARGER)
	return CGAL::SMALLER;
      return CGAL::LARGER;
    }
  
  };
 
  template < class CK >
  class Equal_2
 #ifndef CGAL_CFG_MATCHING_BUG_6
  : public CK::Linear_kernel::Equal_2
#endif
  {
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Circular_arc_2          Circular_arc_2;
    typedef typename CK::Line_arc_2              Line_arc_2;

  public:
    typedef typename  CK::Linear_kernel LK;
    typedef typename LK::Equal_2 LK_Equal_2;

    typedef typename CK::Point_2 Point_2;
    typedef typename CK::Vector_2 Vector_2;
    typedef typename CK::Direction_2 Direction_2;
    typedef typename CK::Segment_2 Segment_2;
    typedef typename CK::Ray_2 Ray_2;
    typedef typename CK::Line_2 Line_2;
    typedef typename CK::Triangle_2 Triangle_2;
    typedef typename CK::Iso_rectangle_2 Iso_rectangle_2;
    typedef typename CK::Circle_2 Circle_2;

    
    typedef typename CK::Linear_kernel::Equal_2::result_type result_type;
#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Equal_2::operator();
#else  

    result_type
    operator() (const Point_2 &p0,
                const Point_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
      
    result_type
    operator() (const Vector_2 &p0,
                const Vector_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
       
    result_type
    operator() (const Vector_2 &p0,
                const Null_vector &p1) const
    { return LK_Equal_2()(p0,p1); }
      
    result_type
    operator() (const Null_vector &p0,
                const Vector_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
      
    result_type
    operator() (const Direction_2 &p0,
                const Direction_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
    
  
    result_type
    operator() (const Segment_2 &p0,
                const Segment_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
    

    result_type
    operator() (const Ray_2 &p0,
                const Ray_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
    
    result_type
    operator() (const Line_2 &p0,
                const Line_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
    


    result_type
    operator() (const Triangle_2 &p0,
                const Triangle_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
    

    result_type
    operator() (const Iso_rectangle_2 &p0,
                const Iso_rectangle_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
    

    result_type
    operator() (const Circle_2 &p0,
                const Circle_2 &p1) const
    { return LK_Equal_2()(p0,p1); }
#endif

    result_type
    operator() (const Circular_arc_point_2 &p0,
                const Circular_arc_point_2 &p1) const
    { return CircularFunctors::equal<CK>(p0, p1); }
    
    result_type
    operator() (const Circular_arc_2 &a0, const Circular_arc_2 &a1) const
    { return CircularFunctors::equal<CK>(a0, a1); }

    result_type
    operator() (const Line_arc_2 &a0, const Line_arc_2 &a1) const
    { return CircularFunctors::equal<CK>(a0, a1); }
    
   };

  template < class CK >
  class Compare_y_at_x_2 : public CK::Linear_kernel::Compare_y_at_x_2
  {
    typedef typename CK::Circular_arc_2          Circular_arc_2;
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Line_arc_2              Line_arc_2;

  public:
    typedef typename CK::Linear_kernel::Compare_y_at_x_2::result_type   result_type;

    using CK::Linear_kernel::Compare_y_at_x_2::operator();    

    result_type
    operator() (const Circular_arc_point_2 &p,
                const Circular_arc_2 &A1) const
    { return CircularFunctors::compare_y_at_x<CK>(p, A1); }

    result_type
    operator() (const Circular_arc_point_2 &p,
                const Line_arc_2 &A1) const
    { return CircularFunctors::compare_y_at_x<CK>(p, A1); }

  };

  template < class CK >
  class Do_overlap_2
  {
    typedef typename CK::Circular_arc_2 Circular_arc_2;
    typedef typename CK::Line_arc_2     Line_arc_2;

  public:
    typedef bool         result_type;
    
    result_type
    operator() (const Circular_arc_2 &A1, const Circular_arc_2 &A2) const
    { return CircularFunctors::do_overlap<CK>(A1, A2); }
    
    result_type
    operator() (const Line_arc_2 &A1, const Line_arc_2 &A2) const
    { return CircularFunctors::do_overlap<CK>(A1, A2); }

  };


  template < class CK >
  class Make_x_monotone_2
  {
    typedef typename CK::Circular_arc_2 Circular_arc_2;
    typedef typename CK::Line_arc_2 Line_arc_2;

  public:
    
     typedef void         result_type;   //!!!

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_2 &A, OutputIterator res) const
    { 
      return    CircularFunctors::make_x_monotone<CK> (A, res);
    }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_2 &A, OutputIterator res) const
    { 
      return CircularFunctors::make_x_monotone<CK>(A,res);
    }

  };

 template < class CK >
  class Make_xy_monotone_2
  {
    typedef typename CK::Circular_arc_2 Circular_arc_2;
    typedef typename CK::Line_arc_2 Line_arc_2;

  public:

     typedef void         result_type;   //!!!

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_2 &A, OutputIterator res) const
      {
        typedef std::pair<bool, bool>                  relat_pos;
        typedef std::pair< CGAL::Object, relat_pos>    Obj_descr_2;
        std::vector<Obj_descr_2> vec;

        CircularFunctors::advanced_make_xy_monotone<CK> (A, std::back_inserter(vec));

        for(unsigned i=0;i<vec.size();++i)
          *res++=vec.at(i).first;

        return res;

      }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_2 &A, OutputIterator res) const
    { *res++ = make_object(A);
      return res;
    }

  };

  template < class CK >
  class Do_intersect_2
    : public CK::Linear_kernel::Do_intersect_2
  {
  public:
    typedef typename CK::Linear_kernel::Do_intersect_2::result_type   result_type;
    template <class T1, class T2>
    result_type
    operator()(const T1& t1, const T2& t2) const
    { return internal::do_intersect(t1, t2, CK()); }
  };
  
  template < class CK >
  class Intersect_2
    : public CK::Linear_kernel::Intersect_2
  {
  
    typedef typename CK::Circle_2                 Circle;
    typedef typename CK::Circular_arc_2           Circular_arc;
    typedef typename CK::Line_arc_2               Line_arc;
    typedef typename CK::Line_2                   Line;
    
    public:

	  typedef typename CK::Linear_kernel::Intersect_2::result_type result_type; 
    
    using CK::Linear_kernel::Intersect_2::operator();

    template < class OutputIterator >
    OutputIterator
    operator()(const Line & c1, const Circle & c2, 
	       OutputIterator res) const
      { return CircularFunctors::intersect_2<CK> (c1,c2,res); }  

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle & c1, const Line & c2, 
	       OutputIterator res) const
      {	return CircularFunctors::intersect_2<CK> (c2,c1,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle & c1, const Circle & c2, OutputIterator res) const
      { return CircularFunctors::intersect_2<CK> (c1,c2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle & c1, const Circular_arc & c2, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (Circular_arc(c1),c2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc & c1, const Circle & c2, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (c1,Circular_arc(c2),res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc & c1, const Circular_arc & c2, 
	       OutputIterator res) const
      { return CircularFunctors::intersect_2<CK> (c1,c2,res); }  

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc & c1, const Line_arc & c2, 
	       OutputIterator res) const
      {	return CircularFunctors::intersect_2<CK> (c1,c2,res); }  

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc & c1, const Circle & c2, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (c1,c2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle & c1, const Line_arc & c2, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (c2,c1,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc & c1, const Circular_arc & c2, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (c1,c2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc & c1, const Line_arc & c2, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (c2,c1,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line & l, const Circular_arc & c, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (l,c,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line & l, const Line_arc & la, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (l,la,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc & c, const Line & l, 
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (l,c,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc & la, const Line & l,
	       OutputIterator res) const
    { return CircularFunctors::intersect_2<CK> (l,la,res); }

  };

  template < class CK >
  class Get_equation
  {
    public:

    typedef void result_type;

    typename CK::Polynomial_1_2
    operator() ( const typename CK::Line_2 & l )
      {
	      return LinearFunctors::get_equation<CK>(l);
      }

    typename CK::Polynomial_for_circles_2_2
    operator() ( const typename CK::Circle_2 & c )
      {
        return CircularFunctors::get_equation<CK>(c);
		  }		
  };

  template < class CK >
  class Split_2
  {
    typedef typename CK::Circular_arc_2          Circular_arc_2;
    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    typedef typename CK::Line_arc_2              Line_arc_2;

  public:

    typedef void         result_type;

    result_type
    operator()(const Circular_arc_2 &A, 
	       const Circular_arc_point_2 &p,
	       Circular_arc_2 &ca1, Circular_arc_2 &ca2) const
    { return CircularFunctors::split<CK>(A, p, ca1, ca2); }


    result_type
    operator()(const Line_arc_2 &A, 
	       const Circular_arc_point_2 &p,
	       Line_arc_2 &ca1, Line_arc_2 &ca2) const
    { return CircularFunctors::split<CK>(A, p, ca1, ca2); }

  };

  template < class CK >
  class Is_vertical_2
    : public CK::Linear_kernel::Is_vertical_2
  {
    typedef typename CK::Circular_arc_2          Circular_arc_2;
    typedef typename CK::Line_arc_2              Line_arc_2;

  public:

	  typedef typename CK::Linear_kernel::Is_vertical_2::result_type result_type; 
    
    using CK::Linear_kernel::Is_vertical_2::operator();

    result_type
    operator()(const Circular_arc_2 &A) const
    { return CircularFunctors::is_vertical<CK>(A); }

    result_type
    operator()(const Line_arc_2 &A) const
    { return CircularFunctors::is_vertical<CK>(A); }

  };

  template < class CK >
  class Construct_circular_arc_2
  {

    typedef typename CK::FT                           FT;
    typedef typename CK::RT                           RT;
    typedef typename CK::Point_2                      Point_2;
    typedef typename CK::Line_2                       Line_2;
    typedef typename CK::Circle_2                     Circle_2;
    typedef typename CK::Circular_arc_2               Circular_arc_2;
    typedef typename CK::Kernel_base::Circular_arc_2  RCircular_arc_2;
    typedef typename Circular_arc_2::Rep              Rep;
    typedef typename CK::Circular_arc_point_2         Circular_arc_point_2;

  public:
    typedef  Circular_arc_2 result_type;
    
    result_type
    operator()(void) 
    { return Rep(); }

    result_type
    operator()(const Circle_2 &c) const
    { return Rep(c); }

    result_type
    operator()(const Circle_2 &support,
               const Circular_arc_point_2 &source, 
               const Circular_arc_point_2 &target) const
    { return Rep(support,source,target); }

    // Not Documented
    result_type
    operator()(const Circle_2 &support,
               const Line_2 &l1, bool b1,
               const Line_2 &l2, bool b2) const
    { return Rep(support,l1,b1,l2,b2); }

    // Not Documented
    result_type
    operator()(const Circle_2 &c,
               const Circle_2 &c1, bool b_1,
               const Circle_2 &c2, bool b_2) const
    { return Rep(c,c1,b_1,c2,b_2); }

    result_type
    operator()(const Point_2 &begin,
               const Point_2 &middle, 
               const Point_2 &end) const
    { return Rep(begin,middle,end); }

    // Not Documented
    result_type
    operator()(const Point_2 &begin,
               const Point_2 &end,
	       const FT& bulge) const
    { return Rep(begin,end,bulge); }

  };

  template < class CK >
  class Construct_line_arc_2
  {

    typedef typename CK::Point_2                   Point_2;
    typedef typename CK::Line_2                    Line_2;
    typedef typename CK::Circle_2                  Circle_2;
    typedef typename CK::Circular_arc_point_2      Circular_arc_point_2;
    typedef typename CK::Segment_2                 Segment_2;
    typedef typename CK::Line_arc_2                Line_arc_2;
    typedef typename CK::Kernel_base::Line_arc_2   RLine_arc_2;
    typedef typename Line_arc_2::Rep               Rep;

  public:
    typedef Line_arc_2   result_type;
    
    result_type
    operator()(void) 
    { return Rep(); }

    // Not Documented
    result_type
    operator()(const Line_2 &support,
	       const Circle_2 &c1,const bool b1,
	       const Circle_2 &c2,const bool b2) const
    { return Rep(support,c1,b1,c2,b2); }

    // Not Documented
    result_type
    operator()(const Line_2 &support,
	       const Line_2 &l1,
	       const Line_2 &l2) const
    { return Rep(support,l1,l2); }

    result_type
    operator()(const Line_2 &support,
	       const Circular_arc_point_2 &p1,
	       const Circular_arc_point_2 &p2) const
    { return Rep(support,p1,p2); }

//     result_type
//     operator()(const Line_2 &support,
// 	       const Point_2 &p1,
// 	       const Point_2 &p2) const
//     { return Rep(support,p1,p2); }

    result_type
    operator()(const Segment_2 &s) const
    { return Rep(s); }

    result_type
    operator()(const Point_2 &p1,
	       const Point_2 &p2) const
    { return Rep(p1,p2); }

  };

  template < class CK >
  class Construct_circular_arc_point_2
  {
    typedef typename CK::Point_2               Point_2;
    typedef typename CK::Circular_arc_point_2  Circular_arc_point_2;
    typedef typename CK::Kernel_base::Circular_arc_point_2  
                                               RCircular_arc_point_2;
    typedef typename Circular_arc_point_2::Rep Rep;
    typedef typename Circular_arc_point_2::Root_for_circles_2_2  
                                               Root_for_circles_2_2;

  public:
    typedef Circular_arc_point_2 result_type;

    result_type
    operator()(void) 
    { return Rep(); }

    result_type
    operator()(const Root_for_circles_2_2 & np) const
    { return Rep(np); }

    result_type
    operator()(const Point_2 & p) const
    { return Rep(p); }

  };


  template <class CK>
  class Compute_circular_x_2: Has_qrt
  {
    typedef typename CK::Circular_arc_point_2   Circular_arc_point_2;
    typedef typename CK::Root_of_2                 Root_of_2;

  public:

    typedef Root_of_2            result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Circular_arc_point_2 & a) const
    {
      return (a.rep().x());
    }
  };


  template <class CK>
  class Compute_circular_y_2: Has_qrt
	{
    typedef typename CK::Circular_arc_point_2   Circular_arc_point_2;
    typedef typename CK::Root_of_2                 Root_of_2;

  public:

    typedef Root_of_2            result_type;
    typedef const result_type &  qualified_result_type;
    
    qualified_result_type operator() (const Circular_arc_point_2 & a) const
    {
      return (a.rep().y());
    }
  };


  template <class CK>
  class Construct_circular_min_vertex_2 : Has_qrt
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Line_arc_2                Line_arc_2;
    typedef typename CK::Circular_arc_point_2      Circular_arc_point_2;

  public:

    typedef Circular_arc_point_2 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Circular_arc_2 & a) const
    {
//       if (a.rep().Cache_minmax == 't')
// 	return (a.rep().source());
//       if (a.rep().Cache_minmax == 's')
// 	return (a.rep().target());
      return (a.rep().left());
    }

    qualified_result_type operator() (const Line_arc_2 & a) const
    {
      return (a.rep().left());
    }

  };

  template <class CK>
  class Construct_circular_max_vertex_2: Has_qrt
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Line_arc_2                Line_arc_2;
    typedef typename CK::Circular_arc_point_2   Circular_arc_point_2;

  public:

    typedef Circular_arc_point_2 result_type;
    typedef const result_type &  qualified_result_type;
    
    qualified_result_type operator() (const Circular_arc_2 & a) const
    {
//       if (a.rep().Cache_minmax == 's')
// 	return (a.rep().source());
//       if (a.rep().Cache_minmax == 't')
// 	return (a.rep().target());
      return (a.rep().right());
    }

    qualified_result_type operator() (const Line_arc_2 & a) const
    {
      return (a.rep().right());
    }

  };

  template <class CK>
  class Construct_circular_source_vertex_2: Has_qrt
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Line_arc_2                Line_arc_2;
    typedef typename CK::Circular_arc_point_2   Circular_arc_point_2;

  public:

    typedef Circular_arc_point_2 result_type;
    typedef const result_type &  qualified_result_type;
    
    qualified_result_type operator() (const Circular_arc_2 & a) const
    { return a.rep().source(); }

    qualified_result_type operator() (const Line_arc_2 & a) const
    { return a.rep().source();}

  };


  template <class CK>
  class Construct_circular_target_vertex_2: Has_qrt
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Line_arc_2                Line_arc_2;
    typedef typename CK::Circular_arc_point_2   Circular_arc_point_2;

  public:

    typedef Circular_arc_point_2 result_type;
    typedef const result_type &  qualified_result_type;
   
    qualified_result_type operator() (const Circular_arc_2 & a) const
    { return a.rep().target();}

    qualified_result_type operator() (const Line_arc_2 & a) const
    { return a.rep().target();}

  };

  template <class CK>
  class Is_x_monotone_2
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Line_arc_2                Line_arc_2;

  public:

    typedef bool         result_type;
    
    result_type operator() (const Circular_arc_2 & a) const
    {
      return (a.rep().is_x_monotone());
    }

    result_type operator() (const Line_arc_2 & a) const
    {
      return (a.rep().is_x_monotone());
    }

  };

  template <class CK>
  class Is_y_monotone_2
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Line_arc_2                Line_arc_2;

  public:

    typedef bool         result_type;
    
    result_type operator() (const Circular_arc_2 & a) const
    {
      return (a.rep().is_y_monotone());
    }

    result_type operator() (const Line_arc_2 & a) const
    {
      return (a.rep().is_y_monotone());
    }

  };

  template <class CK>
  class Construct_bbox_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Construct_bbox_2
#endif
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Circular_arc_point_2      Circular_arc_point_2;
    typedef typename CK::Line_arc_2                Line_arc_2;
    typedef typename CK::Circle_2                  Circle_2;

  public:

    typedef typename CK::Linear_kernel::Construct_bbox_2::result_type result_type; 
#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Construct_bbox_2::operator();
#else
    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Construct_bbox_2 LK_Construct_bbox_2;
    typedef typename CK::Point_2 Point_2;
    typedef typename CK::Segment_2 Segment_2;
    typedef typename CK::Triangle_2  Triangle_2 ;
    typedef typename CK::Iso_rectangle_2 Iso_rectangle_2 ;

    result_type operator() (const Circle_2 & a) const
    {
      return LK_Construct_bbox_2()(a);
    }

    result_type operator() (const Point_2 & a) const
    {
      return LK_Construct_bbox_2()(a);
    }

    result_type operator() (const Segment_2 & a) const
    {
      return LK_Construct_bbox_2()(a);
    }

    result_type operator() (const Triangle_2 & a) const
    {
      return LK_Construct_bbox_2()(a);
    }
    result_type operator() (const Iso_rectangle_2 & a) const
    {
      return LK_Construct_bbox_2()(a);
    }
#endif

    result_type operator() (const Circular_arc_point_2 & a) const
    {
      return a.rep().bbox();
    }

    result_type operator() (const Circular_arc_2 & a) const
    {
      return a.rep().bbox();
    }

    result_type operator() (const Line_arc_2 & a) const
    {
      return a.rep().bbox();
    }

  };

  template <class CK>
  class Bounded_side_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Bounded_side_2
#endif
  {
    typedef typename CK::Circle_2              Circle_2;
    typedef typename CK::Circular_arc_point_2  Circular_arc_point_2;

  public:
    typedef typename CK::Linear_kernel::Bounded_side_2::result_type result_type;

#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Bounded_side_2::operator();
#else 
    typedef typename CK::Point_2 Point_2;
    typedef typename CK::Triangle_2 Triangle_2;
    typedef typename CK::Iso_rectangle_2 Iso_rectangle_2;
    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Bounded_side_2 LK_Bounded_side_2;

    result_type
    operator()(const Circle_2& c, const Point_2& p) const
    { return LK_Bounded_side_2()(c,p); }

    result_type
    operator()(const Triangle_2& c, const Point_2& p) const
    { return LK_Bounded_side_2()(c,p); }

    result_type
    operator()(const Iso_rectangle_2& c, const Point_2& p) const
    { return LK_Bounded_side_2()(c,p); }

#endif

    result_type
    operator()(const Circle_2& c, const Circular_arc_point_2& p) const
    { return CircularFunctors::bounded_side<CK>(c,p); }

  };

  template <class CK>
  class Has_on_bounded_side_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Has_on_bounded_side_2
#endif
  {
    typedef typename CK::Circle_2              Circle_2;
    typedef typename CK::Circular_arc_point_2  Circular_arc_point_2;

  public:
    typedef typename CK::Linear_kernel::Has_on_bounded_side_2::result_type result_type;

#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Has_on_bounded_side_2::operator();
#else
    typedef typename CK::Point_2 Point_2;
    typedef typename CK::Triangle_2 Triangle_2;
    typedef typename CK::Iso_rectangle_2 Iso_rectangle_2;
    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Has_on_bounded_side_2 LK_Has_on_bounded_side_2;

    result_type
    operator()(const Circle_2& c, const Point_2& p) const
    { return LK_Has_on_bounded_side_2()(c,p); }

    result_type
    operator()(const Triangle_2& c, const Point_2& p) const
    { return LK_Has_on_bounded_side_2()(c,p); }

    result_type
    operator()(const Iso_rectangle_2& c, const Point_2& p) const
    { return LK_Has_on_bounded_side_2()(c,p); }
#endif

    result_type
    operator()(const Circle_2& c, const Circular_arc_point_2& p) const
    { return CK().bounded_side_2_object()(c,p) == ON_BOUNDED_SIDE; }

  };

  template <class CK>
  class Has_on_unbounded_side_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Has_on_unbounded_side_2
#endif
  {
    typedef typename CK::Circle_2              Circle_2;
    typedef typename CK::Circular_arc_point_2  Circular_arc_point_2;

  public:
    typedef typename CK::Linear_kernel::Has_on_unbounded_side_2::result_type result_type;

#ifndef CGAL_CFG_MATCHING_BUG_6
    using CK::Linear_kernel::Has_on_unbounded_side_2::operator();
#else 
    typedef typename CK::Point_2 Point_2;
    typedef typename CK::Triangle_2 Triangle_2;
    typedef typename CK::Iso_rectangle_2 Iso_rectangle_2;
    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Has_on_unbounded_side_2 LK_Has_on_unbounded_side_2;

    result_type
    operator()(const Circle_2& c, const Point_2& p) const
    { return LK_Has_on_unbounded_side_2()(c,p); }

    result_type
    operator()(const Triangle_2& c, const Point_2& p) const
    { return LK_Has_on_unbounded_side_2()(c,p); }

    result_type
    operator()(const Iso_rectangle_2& c, const Point_2& p) const
    { return LK_Has_on_unbounded_side_2()(c,p); }
#endif

    result_type
    operator()(const Circle_2& c, const Circular_arc_point_2& p) const
    { return CK().bounded_side_2_object()(c,p) == ON_UNBOUNDED_SIDE; }

  };

#ifndef CGAL_NO_DEPRECATED_CODE
  template <class CK>
  class Construct_supporting_circle_2: Has_qrt
  {
    typedef typename CK::Circular_arc_2            Circular_arc_2;
    typedef typename CK::Circle_2                  Circle_2;

  public:

    typedef Circle_2             result_type;
    
    CGAL_DEPRECATED result_type operator() (const Circular_arc_2 & a) const
    {
      return a.rep().supporting_circle();
    }
  };
  
  
  template <class CK>
  class Construct_supporting_line_2: Has_qrt
  {
    typedef typename CK::Line_arc_2            Line_arc_2;
    typedef typename CK::Line_2                Line_2;
    typedef typename CK::Circle_2              Circle_2;

  public:

    typedef Line_2               result_type;
    
    CGAL_DEPRECATED result_type operator() (const Line_arc_2 & a) const
    {
      return a.rep().supporting_line();
    }
  };
#endif

  template <typename CK>
  class Construct_center_2
	#ifndef CGAL_CFG_MATCHING_BUG_6
	    : public CK::Linear_kernel::Construct_center_2
         #else
  : public  Has_qrt
	#endif
  {
    typedef typename CK::Circular_arc_2  Circular_arc_2;
	  public:

		#ifndef CGAL_CFG_MATCHING_BUG_6
			typedef typename CK::Linear_kernel::Construct_center_2::result_type result_type; 
	    using CK::Linear_kernel::Construct_center_2::operator();
		#else

    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Construct_center_2 LK_Construct_center_2;
	  typedef typename CK::Point_2     Point_2;
	  typedef typename CK::Circle_2    Circle_2;
	public:
    typedef Point_2          result_type;

	  const result_type&
	  operator()( const Circle_2& c) const
	  { return LK_Construct_center_2()(c); }

	#endif

    const result_type&
    operator()(const Circular_arc_2& c) const
    { return c.rep().center(); }

  };

  template <typename CK>
  class Compute_squared_radius_2
#ifndef CGAL_CFG_MATCHING_BUG_6
    : public CK::Linear_kernel::Compute_squared_radius_2
#endif
  {
    typedef typename CK::Circular_arc_2  Circular_arc_2;
  public:

#ifndef CGAL_CFG_MATCHING_BUG_6
    typedef typename CK::Linear_kernel::Compute_squared_radius_2::result_type result_type; 
    using CK::Linear_kernel::Compute_squared_radius_2::operator();
#else

    typedef typename CK::Linear_kernel LK;
    typedef typename LK::Compute_squared_radius_2 LK_Compute_squared_radius_2;
    typedef typename CK::FT          FT;
    typedef typename CK::Point_2     Point_2;
    typedef typename CK::Circle_2    Circle_2;
  public:
    typedef FT               result_type;
    
    const result_type&
    operator()( const Circle_2& c) const
    { return LK_Compute_squared_radius_2()(c); }
    
    result_type
    operator()( const Point_2& p) const
    { return LK_Compute_squared_radius_2()(p); }
    
    result_type
    operator()( const Point_2& p, const Point_2& q) const
    { return LK_Compute_squared_radius_2()(p, q); }
    
    result_type
    operator()( const Point_2& p, const Point_2& q, const Point_2& r) const
    { return LK_Compute_squared_radius_2()(p, q, r); }
    
#endif

    const result_type&
    operator()(const Circular_arc_2& c) const
    { return c.rep().squared_radius(); }

  };

} // namespace CircularFunctors

#ifndef CGAL_CFG_DONT_OVERLOAD_TOO_MUCH
  template < typename K>
  struct Qualified_result_of<CircularFunctors::Construct_center_2<K>,
                           typename K::Circular_arc_2>
  {
    typedef typename K::Point_2 const &   type;
  };

  template < typename K>
  struct Qualified_result_of<CircularFunctors::Compute_squared_radius_2<K>,
                           typename K::Circular_arc_2>
  {
    typedef typename K::FT const &   type;
  };

  template < typename K>
  struct Qualified_result_of<CircularFunctors::Compute_squared_radius_2<K>,
                           typename K::Circle_2>
  {
    typedef typename K::FT const &   type;
  };
#endif

} // namespace CGAL

#endif // CGAL_CIRCULAR_KERNEL_FUNCTION_OBJECTS_POLYNOMIAL_CIRCULAR_H
