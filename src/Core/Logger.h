#pragma once

#include "../Core.h"
#include "LoggerInfo.h"
#include "../Sinks/Sink.h"
#include "../Sinks/ConsoleSink.h"

namespace CoreTrace {
	class Logger {
		public:
			Logger(LoggerInfo info);
			Logger(std::string name);

			void init();
			LoggerFormat genFormat(std::string formatString);
			void setFormat(std::string formatName, std::string format);

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

			template<typename... Args>
			void log(std::string formatName, std::string message, Args&&...args){
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				if(formats.contains(formatName)) {
					m_outputSink->log(formats[formatName], formatted);
				} else {
					m_outputSink->log(msgFormat, formatted);
				}
			}
			
			LoggerFormat traceFormat;
			LoggerFormat msgFormat;
			LoggerFormat warnFormat;
			LoggerFormat fatalFormat;
		
		private:
			std::map<std::string, LoggerFormat> formats;
			LoggerInfo m_info;
			std::shared_ptr<Sinks::Sink> m_outputSink;
	};
}
