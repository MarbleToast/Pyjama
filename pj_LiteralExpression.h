#pragma once
#include "pj_Expression.h"

namespace Pyjama {
	class LiteralExpression : public Expression {};

	class StringLiteralExpression : public LiteralExpression {
		public:
			std::string value;
			StringLiteralExpression(std::string val) : value(val) {}
	};

	class NumberLiteralExpression : public LiteralExpression {
		public:
			int value;
			NumberLiteralExpression(int val) : value(val) {}
	};

	class NoneLiteralExpression : public LiteralExpression {
		public:
			NoneLiteralExpression() = default;
	};
}

