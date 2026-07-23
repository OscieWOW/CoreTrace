#pragma once

#include "../Core/LoggerInfo.h"
#include "../Debug/Serialise.h"

namespace CoreTrace {
	namespace Sinks {
		class USink {
			//The 'U' stands for "Unstructured"
			public:
				USink() = default;

				void init(const std::string& name) {
					m_debugName = name;
				}

				virtual void fatal(std::string message) = 0;

				virtual void warning(std::string message) = 0;
	
				virtual void message(std::string message) = 0;
	
				virtual void trace(std::string message) = 0;

				virtual void log(std::string message) = 0;
	
			protected:
				std::string m_debugName;
		};

		class SSink {
			//The 'S' stands for "Structured"
			public:
				SSink() = default;

				void init(std::string name) {
					m_debugName = name;
				}

				virtual void log(const Node& node) = 0;

			protected:
				std::string m_debugName;
		};
	}
}
