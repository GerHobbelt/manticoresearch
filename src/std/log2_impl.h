//
// Copyright (c) 2017-2023, Manticore Software LTD (https://manticoresearch.com)
// Copyright (c) 2001-2016, Andrew Aksyonoff
// Copyright (c) 2008-2016, Sphinx Technologies Inc
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org
//

#include "ints.h"


#if defined( __GNUC__ ) || defined( __clang__ )

constexpr inline int sphLog2const ( unsigned uValue )
{
	return (int)sizeof ( uValue ) * 8 - __builtin_clz ( uValue | 1 );
}

constexpr inline int sphLog2const ( unsigned long uValue )
{
	return (int)sizeof ( uValue ) * 8 - __builtin_clzl ( uValue | 1 );
}

constexpr inline int sphLog2const ( unsigned long long uValue )
{
	return (int)sizeof ( uValue ) * 8 - __builtin_clzll ( uValue | 1 );
}

inline int sphLog2 ( unsigned uValue )
{
	return sphLog2const ( uValue );
}

inline int sphLog2 ( unsigned long uValue )
{
	return sphLog2const ( uValue );
}

inline int sphLog2 ( unsigned long long uValue )
{
	return sphLog2const ( uValue );
}

#else

namespace {
template<typename UINT>
constexpr inline int Log2constUINT ( UINT uValue )
{
	int iBits = 0;
	do
	{
		uValue >>= 1;
		++iBits;
	} while ( uValue );
	return iBits;
}
}

constexpr inline int sphLog2const ( unsigned uValue )
{
	return Log2constUINT ( uValue );
}

constexpr inline int sphLog2const ( unsigned long uValue )
{
	return Log2constUINT ( uValue );
}

constexpr inline int sphLog2const ( unsigned long long uValue )
{
	return Log2constUINT ( uValue );
}

#if _WIN32

#include <intrin.h> // for bsr
#pragma intrinsic( _BitScanReverse64 )
#pragma intrinsic( _BitScanReverse )

inline int sphLog2 ( unsigned uValue )
{
	DWORD uRes;
	BitScanReverse ( &uRes, uValue | 1 );
	return 1 + uRes;
}

inline int sphLog2 ( unsigned long uValue )
{
	static_assert ( sizeof ( unsigned ) == sizeof ( unsigned long ), "" );
	DWORD uRes;
	BitScanReverse ( &uRes, uValue | 1 );
	return 1 + uRes;
}

inline int sphLog2 ( unsigned long long uValue )
{
	DWORD uRes;
	BitScanReverse64 ( &uRes, uValue | 1 );
	return 1 + uRes;
}


#else

inline int sphLog2 ( unsigned uValue )
{
	return sphLog2const ( uValue );
}

inline int sphLog2 ( unsigned long uValue )
{
	return sphLog2const ( uValue );
}

inline int sphLog2 ( unsigned long long uValue )
{
	return sphLog2const ( uValue );
}

#endif
#endif

inline int sphLog2 ( int iValue )
{
	return sphLog2 ( static_cast<unsigned> ( iValue ) );
}

inline int sphLog2 ( long iValue )
{
	return sphLog2 ( static_cast<unsigned long> ( iValue ) );
}

inline int sphLog2 ( long long iValue )
{
	return sphLog2 ( static_cast<unsigned long long> ( iValue ) );
}