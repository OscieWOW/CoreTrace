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
			LoggerFormat genFormat(std::string formatString);
			
			template<typename... Args>
			void trace(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				m_outputSink->trace(traceFormat, formatted);
			}

			template<typename... Args>
			void message(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				m_outputSink->message(msgFormat, formatted);
			}
			
			template<typename... Args>
			void warning(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				m_outputSink->warning(warnFormat, formatted);
			}

			template<typename... Args>
			void fatal(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				m_outputSink->fatal(fatalFormat, formatted);
			}
		private:
			LoggerInfo m_info;

			LoggerFormat traceFormat;
			LoggerFormat msgFormat;
			LoggerFormat warnFormat;
			LoggerFormat fatalFormat;

			std::shared_ptr<Sinks::Sink> m_outputSink;
	};
}
