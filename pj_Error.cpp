#include "pj_Error.h"

std::string Pyjama::pj_Error::operator()() const noexcept {
    std::string typeStr;

    switch (_type) {
    case ExceptionType::IDENTIFIER:
        typeStr = "[Identifier Error!]";
        break;
    case ExceptionType::TYPE:
        typeStr = "[Type Error!]";
        break;
    case ExceptionType::MATHEMATIC:
        typeStr = "[Maths Error!]";
        break;
    case ExceptionType::SYNTAX:
        typeStr = "[Syntax Error!]";
        break;
    default:
        typeStr = "[Generic Error!]";
        break;
    }

    return (typeStr + " " + _msg);
}
