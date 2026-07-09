#pragma once

#include "Sink.h"

namespace CoreTrace::Sinks {
	class ConsoleSink:public Sink {
		public:
			ConsoleSink() = default;

			void fatal(std::string message) override {
				std::cout << message << std::endl;
			}

			void warning(std::string message) override {
				std::cout << message << std::endl;
			}

			void message(std::string message) override {
				std::cout << message << std::endl;
			}

			void trace(std::string message) override {
				std::cout << message << std::endl;
			}

			void log(std::string message) override {
				std::cout << message << std::endl;
			}
	}; 
}
