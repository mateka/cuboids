#pragma once

// glbinding include with silences warnings
#ifdef _MSC_VER 
	#pragma warning(push)
	#pragma warning(disable: 4305)
#endif	// _MSC_VER  

#define BT_USE_DOUBLE_PRECISION
#include <bullet/btBulletDynamicsCommon.h>

#ifdef _MSC_VER
	#pragma warning(pop)
#endif	// _MSC_VER
