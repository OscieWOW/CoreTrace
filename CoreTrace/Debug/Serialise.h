#pragma once

#include "../Core.h"
#include "DebugEvent.h"

namespace CoreTrace {
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

			template<typename T>
			Node passParameter(const std::chrono::duration<T>& paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName,
					.type = "DURATION",
					.value = std::to_string(paramValue.count())
				};
				return node;
			}
			
			template <typename T>
			Node passParameter(const std::chrono::time_point<T>& paramValue, const std::string& paramName) {
				Node node = {
					.name = paramName, 
					.type = "TIME_POINT",
					.value = std::to_string(paramValue.time_since_epoch().count())
				};
				return node;
			}
		public:
			Node passParameter(const DebugEvent& paramValue, const std::string& paramName) {
				std::vector<Node> children;
				children.push_back(passParameter(paramValue.eventID, "eventID"));
				children.push_back(passParameter(paramValue.functionName, "functionName"));
				children.push_back(passParameter(paramValue.parentProcess, "parentProcess"));
				children.insert(children.end(), paramValue.functionParameters.begin(), paramValue.functionParameters.end());
				if(paramValue.functionReturn) {
					children.push_back(*paramValue.functionReturn);
				}
				children.push_back(passParameter(paramValue.functionStart, "functionStart"));
				children.push_back(passParameter(paramValue.functionEnd, "functionEnd"));
				children.push_back(passParameter(paramValue.functionSuccess, "functionSuccess"));

				Node node = {
					.childNodes = children,
					.name = paramName,
					.type = "NODE",
				};
				return node;
			}
	};
}
