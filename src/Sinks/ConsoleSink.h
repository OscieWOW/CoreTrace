#pragma once

#include "Sink.h"

namespace CoreTrace::Sinks {
	class ConsoleSink:public Sink {
		public:
			ConsoleSink() {}

			std::string formatMessage(LoggerFormat format, std::string message) {
				std::stringstream formatted;
				
				for(auto tk:format.textFormat) {
					switch(tk.formatToken) {
						case('M'):{
							formatted << message;
							break;
						}
						case('N'):{
							formatted << m_info.debugName;
							break;
						}
						case('T'):{
							formatted << tk.value;
							break;
						}
						case('C'): {
							if(tk.value == "W") {
								formatted << "\e[0;37m";
							} else if(tk.value == "G") {
								formatted << "\e[0;32m";
							} else if(tk.value == "Y") {
								formatted << "\e[0;93m";
							} else if(tk.value == "R") {
								formatted << "\e[0;91m";
							}
							break;
						}
					}
				}
				formatted << "\e[0m";
				return formatted.str();
			}

			void fatal(LoggerFormat format, std::string message) override {
				std::cout << formatMessage(format, message) << std::endl;
			}

			void warning(LoggerFormat format, std::string message) override {
				std::cout << formatMessage(format, message) << std::endl;
			}

			void message(LoggerFormat format, std::string message) override {
				std::cout << formatMessage(format, message) << std::endl;
			}

			void trace(LoggerFormat format, std::string message) override {
				std::cout << formatMessage(format, message) << std::endl;
			}
	}; 
}
