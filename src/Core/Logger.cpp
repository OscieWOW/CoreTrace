#include "Logger.h"

namespace CoreTrace {
	void Logger::init() {
		m_outputSink = std::make_shared<Sinks::ConsoleSink>();
		m_outputSink->init(m_info);
		traceFormat = genFormat("%w[%N] %M");
		msgFormat = genFormat("%g[%N] %M");
		warnFormat = genFormat("%y[%N] %M");
		fatalFormat = genFormat("%r[%N] %M");
	}

	void Logger::setFormat(std::string formatName, std::string format) {
		formats[formatName] = genFormat(format);
	}

	LoggerFormat Logger::genFormat(std::string formatString) {
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
			return logFormat;
		}
	Logger::Logger(LoggerInfo info):m_info(info) {
	}
	Logger::Logger(std::string name) {
		m_info = {
			.debugName = name,
			.includeName = true
		};
	}
}
