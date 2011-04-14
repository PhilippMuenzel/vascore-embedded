///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005-2011 Alexander Wemmer, Philipp Münzel and Anton Volkov
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BASICS_H
#define BASICS_H

#if (defined(_WIN32) || defined(__CYGWIN__)) && defined(_MSC_VER)   // Windows && MS Visual C
#    define MSVC_EXPORT __declspec(dllexport)
#    pragma warning( disable : 4996 )   // disable deprecation warnings
#    pragma warning( disable : 4091 )   // disable typedef warning without variable declaration
#    pragma warning( disable : 4275 )   // non &#8211; DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#    pragma warning( disable : 4251 )   // like warning above but for templates (like std::string)
#    pragma warning( disable : 4290 )   // exception handling of MSVC is lousy
#else
#    define MSVC_EXPORT
#endif

#if defined(_MSC_VER)
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#define isnan _isnan
#endif
#include <cmath>

#endif // BASICS_H
