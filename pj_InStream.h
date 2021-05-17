#pragma once
#include <stack>
#include <functional>

namespace Pyjama {
	using InputMethod = std::function<char()>;

	class pj_InStream {

		private:
			/* 
				Input method for retrieving data from some source.
				Must be a function returning an int. 
			*/
			const InputMethod& _input;

			/*
				Stack for keeping hold of tokens after look-ahead.
			*/
			std::stack<char> _lexStack;

			/*
				Current line and character index.
			*/
			size_t _lineNumber,  _charIndex;

		public:
			/*
				Input stream for Pyjama.
				@param in: reference to a constant function returning a char.
			*/
			pj_InStream(const InputMethod& in);

			/*
				Get next character in via input method (_input), or removes from stack if the stream has gone back through the input.
				@returns the next char.
			*/
			char next();

			/*
				Goes back through the input, attaching the input to a stack to be retrieved when going forward again.
				@param c: the character to push back.
			*/
			void back(char c);

			/*
				Gets the current line number.
			*/
			size_t getLineNumber() const;

			/*
				Gets the current character index.
			*/
			size_t getCharIndex() const;
	};
}


