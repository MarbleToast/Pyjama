#pragma once

#include <variant>
#include <iostream>
#include "pj_InStream.h"


namespace Pyjama {
	
	/* 
		Types of token.
		All token types begin with TOKEN.
		Keyword token types are denoted with TOKEN_KW.
		Variable type token types are denoted with TOKEN_VTYPE.
	*/
	enum class TokenType {
		TOKEN_IDENTIFIER,

		TOKEN_KW_NUMBER,
		TOKEN_KW_STRING,
		TOKEN_KW_FUNCTION,

		TOKEN_KW_RETURN,

		TOKEN_VTYPE_NONE,
		TOKEN_VTYPE_UNDEFINED,
		TOKEN_VTYPE_NUMBER,
		TOKEN_VTYPE_STRING,

		TOKEN_LEFT_SQUARE_BRACKET,
		TOKEN_RIGHT_SQUARE_BRACKET,
		TOKEN_LEFT_SMOOTH_BRACKET,
		TOKEN_RIGHT_SMOOTH_BRACKET,
		TOKEN_LEFT_CURLY_BRACKET,
		TOKEN_RIGHT_CURLY_BRACKET,

		TOKEN_COMMA,

		TOKEN_ASSIGNMENT,
		TOKEN_ADD,
		TOKEN_MULTIPLY,
		TOKEN_MINUS,
		TOKEN_DIVIDE,
		TOKEN_MODULO,

		TOKEN_COMP_EQUAL,
		TOKEN_COMP_STRICT_EQUAL,
		TOKEN_COMP_NOT_EQUAL,
		TOKEN_COMP_GT,
		TOKEN_COMP_LT,
		TOKEN_COMP_GTE,
		TOKEN_COMP_LTE,

		TOKEN_NOT,

		TOKEN_INCREMENT,
		TOKEN_DECREMENT,

		TOKEN_UNKNOWN,
		TOKEN_EOF
	};

	struct Identifier {
		std::string name;
	};

	// A token may be of any type from the TokenType enum, an identifier, a double, a string, or a null object.
	using TokenValue = std::variant<TokenType, Identifier, double, std::string, std::monostate>;

	class LexToken {
		/*
			Type of token, from token type. This is strictly the type of the token, not the contents of it.
		*/
		TokenType _type;

		/*
			The plain text from the input; the textual representation of the token.
		*/
		std::string _text;

		/*
			The value of the token, returned in a typed form.
			Note that tokens that signify no explicitly transpilable type return their TokenType enumeration.
		*/
		TokenValue _value;

		size_t _line, _charIndex;

	public:
		LexToken(TokenValue value, std::string text, size_t line, size_t charIndex);

		TokenType getTokenType() const;

		TokenValue getToken() const;

		std::string_view getText() const;

		size_t getLine() const;
		size_t getCharIndex() const;
	};
}


