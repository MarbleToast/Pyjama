#pragma once
#include "pj_Token.h"
#include "pj_Node.h"
#include "pj_Types.h"

namespace Pyjama {
	class Expression : public Node {};

	class TypeExpression : public Expression {
		Type* type;

		TypeExpression(Type* t) :
			type(t)
		{};
	};

	class IdentifierExpression : public Expression {
		Identifier name;

		IdentifierExpression(Identifier i) :
			name(i)
		{};
	};

	class AssignmentExpression : public Expression {
	public:
		class Operator {
		public:
			enum Type {
				ASSIGNMENT
			};
			std::vector<std::tuple<std::string_view, Type>> ops = {
				{"=", Type::ASSIGNMENT}
			};
		};
		Expression* left;
		Operator op;
		Expression* right;

		AssignmentExpression(Expression* lhs, Operator op, Expression* rhs) :
			left(lhs),
			op(op),
			right(rhs)
		{};
	};

	class UnaryExpression : public Expression {
	public:
		class Operator {
		public:
			enum Type {
				POSITIVE,
				NEGATIVE,
				PRE_INC,
				POST_INC,
				PRE_DEC,
				POST_DEC
			};

			/*
				Tuple values:
				0 -> string representation
				1 -> type of operator
				2 -> is postfix operator
			*/
			std::vector<std::tuple<std::string_view, Type, bool>> ops = {
				{"+", Type::POSITIVE, false},
				{"-", Type::NEGATIVE, false},
				{"++", Type::PRE_INC, false},
				{"++", Type::POST_INC, true},
				{"--", Type::PRE_INC, false},
				{"--", Type::POST_INC, true}
			};
		};
		Expression* expression;
		Operator op;

		UnaryExpression(Expression* expr, Operator op) :
			expression(expr),
			op(op)
		{};
	};

	class BinaryExpression : public Expression {
	public:
		class Operator {
		public:
			enum Type {
				EQUAL,
				NOT_EQUAL,
				GT,
				LT,
				GTE,
				LTE,
				ADD,
				DIVIDE,
				MULTIPLY,
				MINUS
			};
			std::vector<std::tuple<std::string_view, Type>> ops = {
				{"==", Type::EQUAL},
				{"!=", Type::NOT_EQUAL},
				{">", Type::GT},
				{"<", Type::LT},
				{">=", Type::GTE},
				{"<=", Type::LTE},
				{"+", Type::ADD},
				{"/", Type::DIVIDE},
				{"*", Type::MULTIPLY},
				{"-", Type::MINUS},
			};
		};
		Expression* left;
		Operator op;
		Expression* right;

		BinaryExpression(Expression* lhs, Operator op, Expression* rhs) :
			left(lhs),
			op(op),
			right(rhs)
		{};
	};
}

