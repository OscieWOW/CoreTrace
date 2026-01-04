#include "../Core.h"

namespace CoreTrace {
	struct LogFormatToken {
		char formatToken;
		std::string value;
	};

	struct LoggerInfo {
		std::string debugName;
		bool includeName;
		std::vector<LogFormatToken> format;

		void genFormat(std::string formatString);
	};

	class Logger {
		public:
			Logger(LoggerInfo info);
			
			template<typename... Args>
			void trace(std::string message, Args&&... args) {
				std::stringstream output;
				
				for(auto token:m_info.format) {
					switch(token.formatToken) {
						case('T'): {
							output << token.value;
							break;
						}
						case('N'): {
							output << m_info.debugName;
							break;	
						}
						case('M'): {
							output << message;
							break;
						}
					}
				}
				
				std::cout << output.str() << std::endl;
			}
			
		private:
			LoggerInfo m_info;
	};
}
