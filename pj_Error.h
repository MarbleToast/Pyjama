#pragma once
#include <stdexcept>
#include <string>
namespace Pyjama {
    enum class ExceptionType {
        SYNTAX,
        MATHEMATIC,
        TYPE,
        IDENTIFIER,
        GENERIC,
    };

    class pj_Error : public std::runtime_error {
        std::string _msg;
        ExceptionType _type;
        int _lineNumber;
        public:
            pj_Error(std::string const& msg, ExceptionType type, int line) :
                _msg(msg),
                _type(type),
                _lineNumber(line),
                std::runtime_error(msg) 
            {};
            pj_Error(const char* const& msg, ExceptionType type, int line) :
                _msg(msg),
                _type(type),
                _lineNumber(line),
                std::runtime_error(msg)
            {};
            virtual std::string operator()() const noexcept;
    };
}


