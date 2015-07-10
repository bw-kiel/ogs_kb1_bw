/**********************************************************************
 * $Id: version.h.vc 2132 2008-07-19 18:20:29Z warmerdam $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2007 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * This is a version header dedicated for use with Microsoft Visual C++
 * compiler.
 * NOTE: Remember to update this file manually when version
 * number changes.
 *
 **********************************************************************/

#ifndef GEOS_VERSION_H
#define GEOS_VERSION_H

#ifndef _MSC_VER
#error "This version.h intended for use with MS Visual C++"
#endif

#define GEOS_VERSION_MAJOR 3
#define GEOS_VERSION_MINOR 0
#define GEOS_VERSION_PATCH 99
#define GEOS_VERSION "3.0svn"
#define GEOS_JTS_PORT "1.7.1"

#endif // GEOS_VERSION_H
