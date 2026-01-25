#include "Logger.h"

namespace CoreTrace {
	void Logger::init() {
		m_outputSink = std::make_shared<Sinks::ConsoleSink>();
		m_outputSink->init(m_info);
		traceFormat = genFormat("[%N] %M");
		msgFormat = genFormat("[%N] %M");
		warnFormat = genFormat("[%N] %M");
		fatalFormat = genFormat("[%N] %M");
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
}
