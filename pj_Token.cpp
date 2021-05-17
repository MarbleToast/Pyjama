#include "pj_Token.h"

Pyjama::LexToken::LexToken(TokenValue value, std::string text, size_t line, size_t charIndex) :
	_text(text),
	_value(std::move(value)),
	_line(line),
	_charIndex(charIndex)
{
    switch (value.index()) {
        case 0:
            _type = std::get<TokenType>(value);
            break;
        case 1:
            _type = TokenType::TOKEN_IDENTIFIER;
            break;
        case 2:
            _type = TokenType::TOKEN_VTYPE_NUMBER;
            break;
        case 3:
            _type = TokenType::TOKEN_VTYPE_STRING;
            break;
        case 4:
            _type = TokenType::TOKEN_EOF;
            break;
        default:
            _type = TokenType::TOKEN_UNKNOWN;
            break;
    }
}

Pyjama::TokenType Pyjama::LexToken::getTokenType() const {
    return _type;
}

Pyjama::TokenValue Pyjama::LexToken::getToken() const {
    switch (_value.index()) {
        case 1:
            return std::get<Identifier>(_value);

        case 2:
            return std::get<double>(_value);

        case 3:
            return std::get<std::string>(_value);

        case 4:
            return std::get<std::monostate>(_value);

        default:
            return std::get<TokenType>(_value);
    }
}

std::string_view Pyjama::LexToken::getText() const {
    return _text;
}

size_t Pyjama::LexToken::getLine() const {
    return _line;
}

size_t Pyjama::LexToken::getCharIndex() const {
    return _charIndex;
}
