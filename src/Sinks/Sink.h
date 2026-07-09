#pragma once

#include "../Core/LoggerInfo.h"

namespace CoreTrace {
	namespace Sinks {
		class Sink {
			public:
				Sink() {}

				void init(std::string name) {
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
	}
}
