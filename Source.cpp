#include <iostream>
#include <sstream>
#include "pj_Lexer.h"
#include "pj_Error.h"
#include "pj_TokenStream.h"

int main() {
	using namespace Pyjama;
	std::cout << "Enter the line to tokenize, or \\n to exit." << std::endl;
	std::string line;

	do {
		if (std::cin.eof()) {
			std::cin.clear();
		}
		std::getline(std::cin, line);
		if (!line.empty()) {
			std::istringstream strstream(line);

			InputMethod input = [&strstream]() {
				return strstream.get();
			};

			try {
				pj_InStream istream(input);
				pj_TokenStream tstream(istream);

				for (LexToken t = *tstream; t.getTokenType() != TokenType::TOKEN_EOF; t = *(++tstream)) {
					std::cout << t.getText() << std::endl;
				}
			}
			catch (const pj_Error& ex) {
				strstream.clear();
				strstream.seekg(0);
				std::cerr << ex() << std::endl;
			}
		}
	} while (!line.empty());

	return EXIT_SUCCESS;
}