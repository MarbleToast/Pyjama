#include "pj_TokenStream.h"
#include "pj_Lexer.h"

namespace Pyjama {
    pj_TokenStream& pj_TokenStream::operator++() {
        tokens.push_back(tokenise(instream));
        return *this;
    }

    const LexToken& pj_TokenStream::operator*(){
        return tokens.back();
    }
    
    const LexToken* pj_TokenStream::operator->() {
        return &tokens.back();
    }

    const std::vector<LexToken> pj_TokenStream::getConsumedTokens() {
        return tokens;
    }
}

