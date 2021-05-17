#pragma once
#include "pj_Token.h"
#include "pj_TokenRegistry.h"
#include <optional>

namespace Pyjama {
	enum class CharacterType {
		ALPHANUMERIC,
		SYMBOL,
		WHITESPACE,
		FILE_END
	};

	CharacterType getCharacterType(char c);

	LexToken getAlphaNumSequence(pj_InStream& instream);
	LexToken getSymbolSequence(pj_InStream& instream);
	LexToken getStringSequence(pj_InStream& instream);

	std::optional<TokenRegistry::const_iterator> getOperator(pj_InStream& instream);

	void skipSingleLineComment(pj_InStream& instream);
	void skipMultiLineComment(pj_InStream& instream);

	LexToken tokenise(pj_InStream& istream);
}

