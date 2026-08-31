#include "Logger.h"

namespace CoreTrace {
	void Logger::init(std::shared_ptr<Sinks::USink> sink, const std::string& colourFormat) {
		if(sink == nullptr) {
			m_outputSink = std::make_shared<Sinks::UConsoleSink>("DEBUG");
		} else {
			sink->init();
			m_outputSink = sink;
		}
		traceFormat = genFormat("%w[%N %D %T] %M", colourFormat);
		msgFormat = genFormat("%g[%N %D %T] %M", colourFormat);
		warnFormat = genFormat("%y[%N %D %T] %M", colourFormat);
		fatalFormat = genFormat("%r[%N %D %T] %M", colourFormat);
	}

	void Logger::setFormat(const std::string& formatName, const std::string& format, const std::string& colourFormat) {
		m_formats[formatName] = genFormat(format, colourFormat);
	}

	LoggerFormat Logger::genFormat(std::string formatString, std::string colourFormatSet) {
			bool formatChar = false;
			std::stringstream text;

			LoggerFormat logFormat;

			for(char token:formatString) {
				if(formatChar) {
					switch(token) {
						case('M'): {
							LogFormatToken tk = {
								.formatToken = 'M',
							};
							logFormat.textFormat.push_back(tk);
							break;
						}	
						case('N'): {
							LogFormatToken tk = {
								.formatToken = 'N'
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
						case('T'): {
							LogFormatToken tk = {
								.formatToken = 't'
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
						case('D'): {
							LogFormatToken tk = {
								.formatToken = 'D'
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
						case('w'): {
							LogFormatToken tk = {
								.formatToken = 'C',
								.value = "W"
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
						case('g'): {
							LogFormatToken tk = {
								.formatToken = 'C',
								.value = "G"
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
						case('y'): {
							LogFormatToken tk = {
								.formatToken = 'C',
								.value = "Y"
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
						case('r'): {
							LogFormatToken tk = {
								.formatToken = 'C',
								.value = "R"
							};
							logFormat.textFormat.push_back(tk);
							break;
						}
					}
					formatChar = false;
				} else if(token != '%') {
					text << token;
				}
				if(token == '%') {
					formatChar = true;
					LogFormatToken tk = {
						.formatToken = 'T',
						.value = text.str()
					};
					logFormat.textFormat.push_back(tk);
					text.str("");
				}
			}
			
			if(colourFormatSet == "ANSI") {
				logFormat.colourFormat = {
					{"W", "\e[0;37m"},
					{"G", "\e[0;32m"},
					{"Y", "\e[0;93m"},
					{"R", "\e[0;91m"}
				};
			} else if(colourFormatSet == "NONE") {
					logFormat.colourFormat = {
						{"W", ""},
						{"G", ""},
						{"Y", ""},
						{"R", ""}
					};
			}

			return logFormat;
		}

	Logger::Logger(const std::string& name):m_debugName(name) {}
	
	std::string Logger::format(std::string msg, LoggerFormat format) {
		std::stringstream formatted;
		
		for(auto tk:format.textFormat) {
			switch(tk.formatToken) {
				case('M'): {
					formatted << msg;
					break;
				}
				case('N'): {
					formatted << m_debugName;
					break;
				}
				case('T'): {
					formatted << tk.value;
					break;
				}
				case('C'): {
					formatted << format.colourFormat[tk.value];
					break;
				}
				case('t'): {
					auto now = std::chrono::system_clock::now();
					std::time_t nowC = std::chrono::system_clock::to_time_t(now);
					struct tm buf;

					#if defined(_MSC_VER)
						localtime_s(&buf, &nowC);
					#else
						localtime_r(&nowC, &buf);
					#endif
					
					formatted << buf.tm_hour << ":" << buf.tm_min << ":" << buf.tm_sec;
					break;
				}
				case('D'): {
					auto now = std::chrono::system_clock::now();
					std::time_t nowC = std::chrono::system_clock::to_time_t(now);
					struct tm buf;

					#if defined(_MSC_VER)
						localtime_s(&buf, &nowC);
					#else
						localtime_r(&nowC, &buf);
					#endif

					formatted << buf.tm_mday << "/" << std::to_string(1 + buf.tm_mon) << "/" << std::to_string(1900 + buf.tm_year);
					break;
				}
			}
		}
		formatted << format.colourFormat["W"];
		return formatted.str();
	}

	std::string Logger::getName() {
		return m_debugName;
	}
}
