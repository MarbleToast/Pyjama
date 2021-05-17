#pragma once
#include "pj_InStream.h"
#include "pj_Token.h"

namespace Pyjama {
	class pj_TokenStream {

		pj_InStream instream;
		std::vector<LexToken> tokens = {};

		public:
			pj_TokenStream(pj_InStream& in) : instream(in) { ++(*this); };

			pj_TokenStream& operator++();

			const LexToken& operator*();
			const LexToken* operator->();
			const std::vector<LexToken> getConsumedTokens();
	};
}

