#pragma once
#include <string>
#include <vector>
#include "pj_Node.h"

namespace Pyjama {
	class Type : public Node {
		protected:
			std::string name;
			Type(std::string n) : name(n) {};
		public:
			std::string toString() const noexcept { return name; };
	};

	class PrimativeType final : public Type {
		public:
			PrimativeType(std::string n) : Type(n) {}
	};

	class FunctionType final : public Type {
		public:
			struct Parameter {
				Type type;
			};
		private:
			Type returnType;
			std::vector<Parameter> params;
		public:
			FunctionType(std::string n, Type r, std::vector<Parameter> p) : Type(n), returnType(r), params(p) {}
	};
}


