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
	};
}
