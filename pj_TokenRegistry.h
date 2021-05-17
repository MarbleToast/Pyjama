#pragma once
#include "pj_Token.h"
#include <map>

namespace Pyjama {

	using TokenRegistry = std::map<std::string_view, TokenType>;

	const TokenRegistry keywordMap{
		{ "string", TokenType::TOKEN_KW_STRING },
		{ "number", TokenType::TOKEN_KW_NUMBER },
		{ "func", TokenType::TOKEN_KW_FUNCTION },

		{ "return", TokenType::TOKEN_KW_RETURN },

		{ "none", TokenType::TOKEN_VTYPE_NONE },
	};

	const TokenRegistry operatorMap{
		{ "=", TokenType::TOKEN_ASSIGNMENT },
		{ "+", TokenType::TOKEN_ADD },
		{ "*", TokenType::TOKEN_MULTIPLY },
		{ "-", TokenType::TOKEN_MINUS },
		{ "/", TokenType::TOKEN_DIVIDE },
		{ "%", TokenType::TOKEN_MODULO },

		{ ",", TokenType::TOKEN_COMMA },

		{ "[", TokenType::TOKEN_LEFT_SQUARE_BRACKET },
		{ "]", TokenType::TOKEN_RIGHT_SQUARE_BRACKET },
		{ "(", TokenType::TOKEN_LEFT_SMOOTH_BRACKET },
		{ ")", TokenType::TOKEN_RIGHT_SMOOTH_BRACKET },
		{ "{", TokenType::TOKEN_LEFT_CURLY_BRACKET },
		{ "}", TokenType::TOKEN_RIGHT_CURLY_BRACKET },

		{ "!", TokenType::TOKEN_NOT },

		{ "==", TokenType::TOKEN_COMP_EQUAL },
		{ "===", TokenType::TOKEN_COMP_STRICT_EQUAL},
		{ "!=", TokenType::TOKEN_COMP_NOT_EQUAL },
		{ ">", TokenType::TOKEN_COMP_GT },
		{ "<", TokenType::TOKEN_COMP_LT },
		{ ">=", TokenType::TOKEN_COMP_GTE },
		{ "<=", TokenType::TOKEN_COMP_LTE },

		{ "++", TokenType::TOKEN_INCREMENT },
		{ "--", TokenType::TOKEN_DECREMENT },
	};
}