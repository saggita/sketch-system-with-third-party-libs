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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Stream_support/include/CGAL/IO/Verbose_ostream.h $
// $Id: Verbose_ostream.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>

#ifndef CGAL_IO_VERBOSE_OSTREAM_H
#define CGAL_IO_VERBOSE_OSTREAM_H

#include <iostream>

namespace CGAL {

#define CGAL__VERB(x) if (b) *o << x; return *this

class Verbose_ostream {
    bool          b;
    std::ostream* o;
public:
    Verbose_ostream( bool active = false, std::ostream& out = std::cerr)
        : b(active), o(&out){}

    bool          verbose()           const { return b; }
    void          set_verbose(bool active)  { b = active; }
    std::ostream& out()                     { return *o; }

    template < class T >
    Verbose_ostream& operator<<(const T& t)
    { CGAL__VERB(t); }

    Verbose_ostream& operator<<( std::ostream& (*f)(std::ostream&))
    { CGAL__VERB(f); }

    Verbose_ostream& operator<<( std::ios& (*f)(std::ios&))
    { CGAL__VERB(f); }

    Verbose_ostream& flush()
    {
        if (b)
            o->flush();
        return *this;
    }

    Verbose_ostream& put(char c)
    {
        if (b)
            o->put(c);
        return *this;
    }

    Verbose_ostream& write(const char* s, int n)
    {
        if (b)
            o->write(s, n);
        return *this;
    }
};

} //namespace CGAL

#endif // CGAL_IO_VERBOSE_OSTREAM_H
