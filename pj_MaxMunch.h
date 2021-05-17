#pragma once
#include "pj_Token.h"

/*
    Struct for holding a string to TokenType representation. Uses string view for reference passing.
*/


namespace Pyjama {
    using TokenTextPair = const std::pair<const std::string_view, TokenType>;
    class MaxMunch {
        private:
            size_t _index;
        public:
            MaxMunch(size_t index);

            /*
                Returns true if the left-hand character is less than the right-hand character.
            */
            bool operator()(char lhs, char rhs) const;

            /*
                Returns true if the left-hand Token is less than the right-hand character.
            */
            bool operator()(TokenTextPair lhs, char rhs) const;

            /*
                Returns true if the left-hand character is less than the right-hand Token.
            */
            bool operator()(char lhs, TokenTextPair rhs) const;

            /*
                Returns true if the left-hand Token is less than the right-hand Token.
            */
            bool operator()(TokenTextPair lhs, TokenTextPair rhs) const;
    };
}