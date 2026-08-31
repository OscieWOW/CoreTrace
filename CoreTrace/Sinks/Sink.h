#pragma once

#include "../Core/LoggerInfo.h"
#include "../Debug/Serialise.h"

namespace CoreTrace {
	namespace Sinks {
		class USink {
			//The 'U' stands for "Unstructured"
			public:
				USink(const std::string& name = "DEBUG"):m_debugName(name) {}
				
				void setName(const std::string& name) {
					m_debugName = name;
				}

				virtual void init() = 0;

				virtual void fatal(const std::string& message) = 0;

				virtual void warning(const std::string& message) = 0;
	
				virtual void message(const std::string& message) = 0;
	
				virtual void trace(const std::string& message) = 0;

				virtual void log(const std::string& message) = 0;
	
			protected:
				std::string m_debugName;
		};

		class SSink {
			//The 'S' stands for "Structured"
			public:
				SSink(const std::string& name):m_debugName(name) {}

				virtual void init() = 0;

				virtual void log(const Node& node) = 0;

			protected:
				std::string m_debugName;
		};
	}
}
