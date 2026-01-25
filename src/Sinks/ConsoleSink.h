#pragma once

#include "Sink.h"

namespace CoreTrace::Sinks {
	class ConsoleSink:public Sink {
		public:
			ConsoleSink() {}

			void fatal(std::string message) override {}

			void warning(std::string message) override {}

			void message(std::string message) override {}

			void trace(std::string message) override {std::cout << message << std::endl;}
	}; 
}
