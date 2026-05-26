#pragma once

#include "../Core.h"

namespace CoreTrace {
	enum class NodeType {
		PARENT,
		CHILD
	};

	struct Node {
		int parentNode = 0;
		NodeType nodeType = NodeType::PARENT;

		std::string name = "";
		std::string type = "";
		std::string value = ""; 
	};

	class Serialise {
		public:
			Serialise() = default;

			void setName(const std::string& functionName) {
				Node node = {
					.name = functionName
				};
				m_nodeStack.push_back(node);
			}

			void addParameter(int paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "INTEGER",
					.value = std::to_string(paramValue)
				};
				m_nodeStack.push_back(node);
			}
			
			void addParameter(const std::string& paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "STRING",
					.value = paramValue
				};
				m_nodeStack.push_back(node);
			}

			void addParameter(const char paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "CHAR",
					.value = std::string(1, paramValue)
				};
				m_nodeStack.push_back(node);
			}
			/*
			------------------------------------
			-----ADD THE SERIALISATION CODE-----
			------------------------------------ 
			*/

			std::vector<Node> extractNodes() {
				return m_nodeStack;
			}

		protected:
			std::vector<Node> m_nodeStack;
	};
}
