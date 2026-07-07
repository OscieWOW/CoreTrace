#pragma once

#include "../Core.h"

namespace CoreTrace {
	struct Node {
		std::vector<int> childNodeID;

		std::string name = "";
		std::string type = "";
		std::string value = ""; 
	};

	class Serialise {
		public:
			Serialise() = default;

			Node passParameter(int paramValue, const std::string& paramName) {
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
			/*
			------------------------------------
			-----ADD THE SERIALISATION CODE-----
			------------------------------------ 
			*/
	};
}
