// Copyright (c) 2006 Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Arrangement_on_surface_2/include/CGAL/Arr_topology_traits/Arr_spherical_batched_pl_helper.h $
// $Id: Arr_spherical_batched_pl_helper.h 56667 2010-06-09 07:37:13Z sloriot $
// 
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>
//                 Ron Wein <wein@post.tau.ac.il>
//                 Efi Fogel <efif@post.tau.ac.il>
//

#ifndef CGAL_ARR_SPHERICAL_BATCHED_PL_HELPER_H
#define CGAL_ARR_SPHERICAL_BATCHED_PL_HELPER_H

/*! \file
 * Definition of the Arr_spherical_batched_pl_helper class-template.
 */

namespace CGAL {

#include <CGAL/Sweep_line_empty_visitor.h>

/*! \class Arr_spherical_batched_pl_helper
 * A helper class for the batched point-location sweep-line visitor, suitable
 * for an Arrangement_on_surface_2 instantiated with a topology-traits class
 * for bounded curves in the plane.
 */
template <class Traits_, class Arrangement_>
class Arr_spherical_batched_pl_helper
{
public:

  typedef Traits_                                      Traits_2;
  typedef Arrangement_                                 Arrangement_2;

  typedef typename Arrangement_2::Face_const_handle    Face_const_handle;

  typedef Sweep_line_empty_visitor<Traits_2>           Base_visitor;
  typedef typename Base_visitor::Event                 Event;
  typedef typename Base_visitor::Subcurve              Subcurve;

protected:

  typedef typename Arrangement_2::Topology_traits      Topology_traits;

  // Data members:
  //! The topology-traits class.
  const Topology_traits * m_top_traits;

  //! The unbounded arrangement face.
  Face_const_handle m_unb_face;

public:
  /*! Constructor.
   * \param arr The arrangement.
   */
  Arr_spherical_batched_pl_helper(const Arrangement_2 *arr) :
    m_top_traits(arr->topology_traits())
  {}

  /// \name Notification functions.
  //@{

  /*! A notification issued before the sweep process starts. */
  void before_sweep()
  {
    // Get the unbounded face.
    m_unb_face = Face_const_handle(m_top_traits->unbounded_face());
  }

  /*! A notification invoked after the sweep-line finishes handling the given
   * event.
   */
  void after_handle_event(Event * event) { return; }
  //@}

  /*! Get the current top face. */
  Face_const_handle top_face() const
  {
    return m_unb_face;
  }
};

} //namespace CGAL

#endif
