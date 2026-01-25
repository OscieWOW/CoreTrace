#pragma once

#include "../Core/LoggerInfo.h"

namespace CoreTrace {
	namespace Sinks {
		class Sink {
			public:
				Sink() {}

				void init(LoggerInfo info) {
					m_info = info;
				}

				virtual void fatal(std::string message) = 0;

				virtual void warning(std::string message) = 0;
	
				virtual void message(std::string message) = 0;
	
				virtual void trace(std::string message) = 0;
	
			private:
				CoreTrace::LoggerInfo m_info;
		};
	}
}
