#include "pj_TypeRegistry.h"

namespace Pyjama {
	PrimativeType pj_TypeRegistry::stringType = PrimativeType("string");
	PrimativeType pj_TypeRegistry::numberType = PrimativeType("number");
	PrimativeType pj_TypeRegistry::noneType = PrimativeType("none");
}