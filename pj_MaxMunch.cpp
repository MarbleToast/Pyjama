#include "pj_MaxMunch.h"

Pyjama::MaxMunch::MaxMunch(size_t index) : _index(index) {}

bool Pyjama::MaxMunch::operator()(char lhs, char rhs) const {
    return lhs < rhs;
}

bool Pyjama::MaxMunch::operator()(
    TokenTextPair lhs,
    char rhs
) const {
    return lhs.first.size() <= _index || lhs.first[_index] < rhs;
}

bool Pyjama::MaxMunch::operator()(
    char lhs,
    TokenTextPair rhs
) const {
    return rhs.first.size() > _index && lhs < rhs.first[_index];
}

bool Pyjama::MaxMunch::operator()(
    TokenTextPair lhs,
    TokenTextPair rhs
) const {
    return rhs.first.size() > _index && (lhs.first.size() < _index || lhs.first[_index] < rhs.first[_index]);
}