#pragma once

#include "../Core.h"
#include "LoggerInfo.h"
#include "../Sinks/Sink.h"
#include "../Sinks/ConsoleSink.h"
#include "../Sinks/FileSink.h"

namespace CoreTrace {
	class Logger {
		public:
			Logger(const std::string& name = "DEBUG");

			void init(std::shared_ptr<Sinks::USink> sink = nullptr, const std::string& coloutFormat = "ANSI");
			LoggerFormat genFormat(std::string formatString, std::string colourFormatSet = "ANSI");
			void setFormat(const std::string& formatName, const std::string& format, const std::string& colourFormat = "ANSI");

			template<typename... Args>
			void trace(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				formatted = format(formatted, traceFormat);
				m_outputSink->trace(formatted);
			}

			template<typename... Args>
			void message(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				formatted = format(formatted, msgFormat);
				m_outputSink->message(formatted);
			}
			
			template<typename... Args>
			void warning(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				formatted = format(formatted, warnFormat);
				m_outputSink->warning(formatted);
			}

			template<typename... Args>
			void fatal(std::string message, Args&&... args) {
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				formatted = format(formatted, fatalFormat);
				m_outputSink->fatal(formatted);
			}

			template<typename... Args>
			void log(std::string formatName, std::string message, Args&&...args){
				auto formatted = std::vformat(
					std::string_view(message),
					std::make_format_args(args...)
				);
				if(m_formats.contains(formatName)) {
					formatted = format(formatted, m_formats[formatName]);
					m_outputSink->log(formatted);
				} else {
					m_outputSink->log(formatted);
				}
			}

			std::string format(std::string msg, LoggerFormat format);

			std::string getName();
			
			LoggerFormat traceFormat;
			LoggerFormat msgFormat;
			LoggerFormat warnFormat;
			LoggerFormat fatalFormat;
		
		private:
			std::map<std::string, LoggerFormat> m_formats;
			std::string m_debugName;
			std::shared_ptr<Sinks::USink> m_outputSink;
	};
}
