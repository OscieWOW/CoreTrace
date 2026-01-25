#pragma once

#include "Sink.h"

namespace CoreTrace::Sinks {
	class ConsoleSink:public Sink {
		public:
			ConsoleSink() {}

			std::string formatMessage(LoggerFormat format, std::string message) {
				return message;
			}

			void fatal(LoggerFormat format, std::string message) override {}

			void warning(LoggerFormat format, std::string message) override {}

			void message(LoggerFormat format, std::string message) override {}

			void trace(LoggerFormat format, std::string message) override {
				std::cout << formatMessage(format, message) << std::endl;
			}
	}; 
}
