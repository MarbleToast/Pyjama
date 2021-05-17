#include "pj_Lexer.h"
#include "pj_Error.h"
#include <cctype>
#include "pj_MaxMunch.h"
#include <algorithm>

namespace Pyjama {
    CharacterType getCharacterType(char c) {
        if (c == std::char_traits<char>::eof())
            return CharacterType::FILE_END;
        else if (isalnum(c) || c == '_')
            return CharacterType::ALPHANUMERIC;
        else if (isspace(c))
            return CharacterType::WHITESPACE;
        else
            return CharacterType::SYMBOL;
    }

    std::optional<TokenType> getKeyword(std::string_view kw) {
        auto pair = keywordMap.find(kw);
        return (pair == keywordMap.end()) ? std::nullopt : std::make_optional(pair->second);
    }

    std::optional<TokenRegistry::const_iterator> getOperator(pj_InStream& instream) {
        auto possibles = std::make_pair(Pyjama::operatorMap.begin(), Pyjama::operatorMap.end());

        std::optional<TokenRegistry::const_iterator> value;
        size_t matchLength = 0;
        std::stack<int> characters;

        for (size_t idx = 0; possibles.first != possibles.second; ++idx) {
            characters.push(instream.next());

            possibles = std::equal_range(
                possibles.first,
                possibles.second,
                char(characters.top()),
                MaxMunch(idx)
            );

            if (possibles.first != possibles.second && possibles.first->first.size() == idx + 1) {
                matchLength = idx + 1;
                value = possibles.first;
            }
        }

        while (characters.size() > matchLength) {
            instream.back(characters.top());
            characters.pop();
        }

        return value;
    }

    LexToken getAlphaNumSequence(pj_InStream& instream) {
        std::string seq = "";
        char c = instream.next();
        bool isNumberSeq = std::isdigit(c);

        do {
            seq.push_back(c);
            c = instream.next();
        } while (getCharacterType(c) == CharacterType::ALPHANUMERIC || (isNumberSeq && c == '.'));

        instream.back(c);
        if (std::optional<TokenType> keyword = getKeyword(seq)) {
            return LexToken(*keyword, seq, instream.getLineNumber(), instream.getCharIndex());
        }

        if (std::isdigit(seq.front())) {
            char* end;
            double num = std::strtol(seq.c_str(), &end, 0);
            if (*end) {
                num = std::strtod(seq.c_str(), &end);
                if (*end) {
                    throw pj_Error(
                        std::string(1, char(*end)),
                        ExceptionType::GENERIC,
                        instream.getLineNumber()
                    );
                }
            }
            return LexToken(num, seq, instream.getLineNumber(), instream.getCharIndex());
        }

        return LexToken(Identifier{seq}, seq, instream.getLineNumber(), instream.getCharIndex());
    }

    LexToken getSymbolSequence(pj_InStream& instream) {
        if (auto t = getOperator(instream)) {
            return LexToken((*t)->second, (*t)->first.data(), instream.getLineNumber(), instream.getCharIndex());
        }

        std::string badSequence;
        char c = instream.next();
        do {
            badSequence.push_back(c);
            c = instream.next();
        } while (getCharacterType(c) == CharacterType::SYMBOL);
        instream.back(c);

        throw pj_Error("Bad operator: " + badSequence, ExceptionType::SYNTAX, instream.getLineNumber());
    }

    LexToken getStringSequence(pj_InStream& instream) {
        std::string seq = "";
        char c = instream.next();
        do {
            switch (c) {
                case '\\': {
                    char oneMore = instream.next();
                    switch (oneMore) {
                    case 'r':
                        seq.push_back('\r');
                        break;
                    case 't':
                        seq.push_back('\t');
                        break;
                    case 'n':
                        seq.push_back('\n');
                        break;
                    case 'v':
                        seq.push_back('\v');
                        break;
                    case 'f':
                        seq.push_back('\f');
                        break;
                    case 'b':
                        seq.push_back('\b');
                        break;
                    case '\'':
                        seq.push_back('\'');
                        break;
                    case '"':
                        seq.push_back('\"');
                        break;
                    }
                }
                case '\n':
                case '\r':
                    instream.back(c);
                    // exception
                    throw pj_Error("Missing closing \"", ExceptionType::SYNTAX, instream.getLineNumber());
                case '\"':
                    return LexToken(std::move(seq), std::move(seq), instream.getLineNumber(), instream.getCharIndex());
                default:
                    seq.push_back(c);
            }
            c = instream.next();
        } while (getCharacterType(c) != CharacterType::FILE_END);

        instream.back(c);
        throw pj_Error("Missing closing \"", ExceptionType::SYNTAX, instream.getLineNumber());
    }

    void skipSingleLineComment(pj_InStream& instream) {
        char c = instream.next();
        do {
            c = instream.next();
        } while (c != '\n' && getCharacterType(c) != CharacterType::FILE_END);

        if (c != '\n')
            instream.back(c);
    }

    void skipMultiLineComment(pj_InStream& instream) {
        char c = instream.next();
        do {
            if (c == '*') {
                char oneMore = instream.next();
                if (oneMore == '/') break;
                instream.back(oneMore);
            }
            c = instream.next();
        } while (getCharacterType(c) != CharacterType::FILE_END);
    }

    LexToken Pyjama::tokenise(pj_InStream& istream) {
        while (true) {
            char nextChar = istream.next();
            size_t lineNumber = istream.getLineNumber();
            size_t charIndex = istream.getCharIndex();

            CharacterType nextCharType = getCharacterType(nextChar);

            switch (nextCharType)
            {
                case Pyjama::CharacterType::ALPHANUMERIC: 
                    istream.back(nextChar); // Go back one character to capture the whole sequence of characters
                    return getAlphaNumSequence(istream);
            
                case Pyjama::CharacterType::SYMBOL: 
                    switch (nextChar) {
                        case '\"':
                            return getStringSequence(istream);

                        case '/': {
                            char oneMore = istream.next();
                            switch (oneMore) {
                            case '/':
                                skipSingleLineComment(istream);
                                continue;

                            case '*':
                                skipMultiLineComment(istream);
                                continue;

                            default:
                                istream.back(oneMore);
                                
                            }
                        }
                            
                        default:
                            istream.back(nextChar);
                            return getSymbolSequence(istream);
                    }
                    
                case Pyjama::CharacterType::WHITESPACE: 
                    continue;
            
                case Pyjama::CharacterType::FILE_END:
                    return { std::monostate(), "<eof>", lineNumber, charIndex };

                default:
                    break; 
            }
        }
    }
}

