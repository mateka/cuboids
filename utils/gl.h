#pragma once

// glbinding include with silences warnings
#ifdef _MSC_VER 
	#pragma warning(push)
	#pragma warning(disable: 4251)
#endif	// _MSC_VER  

#include <glbinding/gl43core/gl.h>
#include <glbinding/Binding.h>

#ifdef _MSC_VER
	#pragma warning(pop)
#endif	// _MSC_VER
