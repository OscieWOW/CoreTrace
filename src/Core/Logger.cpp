#include "Logger.h"

namespace CoreTrace {
	void LoggerInfo::genFormat(std::string formatString) {
		bool formatChar = false;
		std::stringstream text;

		for(char token:formatString) {
			if(formatChar) {
				switch(token) {
					case('M'): {
						LogFormatToken tk = {
							.formatToken = 'M',
						};
						format.push_back(tk);
						break;
					}
					case('N'): {
						LogFormatToken tk = {
							.formatToken = 'N'
						};
						format.push_back(tk);
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
				format.push_back(tk);
				text.str("");
			}
		}	
	}

	Logger::Logger(LoggerInfo info):m_info(info) {
	}	
}
