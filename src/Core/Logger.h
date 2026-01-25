#pragma once

#include "../Core.h"
#include "LoggerInfo.h"
#include "../Sinks/Sink.h"
#include "../Sinks/ConsoleSink.h"

namespace CoreTrace {
	class Logger {
		public:
			Logger(LoggerInfo info);
			void init();
			
			template<typename... Args>
			void trace(std::string message, Args&&... args) {
				//formating of string arguments
				m_outputSink->trace(message);
			}
			
		private:
			LoggerInfo m_info;
			std::shared_ptr<Sinks::Sink> m_outputSink;
	};
}
