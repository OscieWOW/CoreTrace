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

				virtual void fatal(LoggerFormat format, std::string message) = 0;

				virtual void warning(LoggerFormat format, std::string message) = 0;
	
				virtual void message(LoggerFormat format, std::string message) = 0;
	
				virtual void trace(LoggerFormat format, std::string message) = 0;
	
			private:
				CoreTrace::LoggerInfo m_info;
		};
	}
}
