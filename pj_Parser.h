#pragma once
#include <set>
#include "pj_Token.h"
#include "pj_TokenStream.h"
#include "pj_Node.h"

namespace Pyjama {
	class pj_Parser {
		pj_TokenStream tstream;
		public:
			pj_Parser(pj_TokenStream& ts) : tstream(ts) {};
	};
}


