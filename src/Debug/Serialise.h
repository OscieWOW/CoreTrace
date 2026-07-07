#pragma once

#include "../Core.h"

namespace CoreTrace {
	struct Node {
		std::vector<Node> childNodes;

		std::string name = "";
		std::string type = "";
		std::string value = ""; 
	};

	class Serialise {
		public:
			Serialise() = default;

			Node passParameter(const int& paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "INTEGER",
					.value = std::to_string(paramValue)
				};
				return node;
			}
			
			Node passParameter(const std::string& paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "STRING",
					.value = paramValue
				};
				return node;
			}

			Node passParameter(const char paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "CHAR",
					.value = std::string(1, paramValue)
				};
				return node;
			}
			
			template <typename T>
			Node passParameter(const std::vector<T>& paramValue, const std::string& paramName) {
				std::vector<Node> values;
				for(const auto& value:paramValue) {
					values.push_back(passParameter(value, ""));
				}
				Node node = {
					.childNodes = values,
					.name = paramName,
					.type = "VECTOR"
				};
				return node;
			}
			/*
			------------------------------------
			-----ADD THE SERIALISATION CODE-----
			------------------------------------ 
			*/
	};
}
