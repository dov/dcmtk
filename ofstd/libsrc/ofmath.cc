/*
 *
 *  Copyright (C) 2015, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  ofstd
 *
 *  Author:  Jan Schlamelcher
 *
 *  Purpose: Platform independent definition of basic functions declared
 *           in <math.h> resp. <cmath>.
 *
 */


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define INCLUDE_CMATH
#define INCLUDE_CFLOAT
#include "dcmtk/ofstd/ofstdinc.h"
#include "dcmtk/ofstd/ofstd.h"
#include <math.h>

#ifdef HAVE_WINDOWS_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#define _isnan(x) isnan(x)

/* Some MacOS X versions define isinf() and isnan() in <math.h> but not in <cmath> */
#if defined(__APPLE__) && defined(__MACH__) && !defined (__INTEL_COMPILER)
#undef HAVE_PROTOTYPE_ISINF
#undef HAVE_PROTOTYPE_ISNAN
#endif


// some systems don't properly define isnan()
#ifdef HAVE_ISNAN
#ifndef HAVE_PROTOTYPE_ISNAN
extern "C"
{
  int isnan(double value);
}
#endif
#endif


// some systems don't properly define finite()
#ifdef HAVE_FINITE
#ifndef HAVE_PROTOTYPE_FINITE
extern "C"
{
  int finite(double value);
}
#endif
#endif

#if !defined(HAVE_ISINF) && defined(HAVE_PROTOTYPE_ISINF)
#   define HAVE_ISINF 1
#endif

OFBool OFStandard::isnan( float f )
{
#ifdef HAVE_WINDOWS_H
  return _isnan(f) != 0;
#elif defined(HAVE_PROTOTYPE_STD__ISNAN)
  return STD_NAMESPACE isnan(f);
#else
  return ::isnan(f);
#endif
}

OFBool OFStandard::isnan( double d )
{
#ifdef HAVE_WINDOWS_H
  return _isnan(d) != 0;
#elif defined(HAVE_PROTOTYPE_STD__ISNAN)
  return STD_NAMESPACE isnan(d);
#else
  return ::isnan(d);
#endif
}

OFBool OFStandard::isinf( float f )
{
  return STD_NAMESPACE isinf( f );
}

OFBool OFStandard::isinf( double d )
{
  return STD_NAMESPACE isinf( d );
}
