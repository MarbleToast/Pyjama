#include "pj_InStream.h"

Pyjama::pj_InStream::pj_InStream(const InputMethod& in):
	_input(in),
	_lineNumber(0),
	_charIndex(0)
{}

char Pyjama::pj_InStream::next() {
	char nextChar = 0;

	// If our backtrack stack is empty then get the next number,
	// otherwise get the top thing from out backtrack stack
	if (_lexStack.empty()) {
		nextChar = _input();
	}
	else {
		nextChar = _lexStack.top();
		_lexStack.pop();
	}

	if (nextChar == '\n') {
		++_lineNumber;
	}

	++_charIndex;

	return nextChar;
}

void Pyjama::pj_InStream::back(char c) {
	// Add to our backtrack stack
	_lexStack.push(c);
	if (c == '\n') {
		--_lineNumber;
	}
	--_charIndex;
}

size_t Pyjama::pj_InStream::getLineNumber() const {
	return _lineNumber;
}

size_t Pyjama::pj_InStream::getCharIndex() const {
	return _charIndex;
}
