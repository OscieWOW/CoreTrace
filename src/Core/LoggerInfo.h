#pragma once

#include "../Core.h"

namespace CoreTrace {
	struct LogFormatToken {
		char formatToken;
		std::string value;
	};
	struct LoggerFormat {
		std::vector<LogFormatToken> textFormat;
	};
	struct LoggerInfo {
		std::string debugName;
		bool includeName;
		LoggerFormat format;

		void genFormat(std::string formatString) {
			bool formatChar = false;
			std::stringstream text;

			for(char token:formatString) {
				if(formatChar) {
					switch(token) {
						case('M'): {
							LogFormatToken tk = {
								.formatToken = 'M',
							};
							format.textFormat.push_back(tk);
							break;
						}	
						case('N'): {
							LogFormatToken tk = {
								.formatToken = 'N'
							};
							format.textFormat.push_back(tk);
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
					format.textFormat.push_back(tk);
					text.str("");
				}
			}	
		}	
	};
}
