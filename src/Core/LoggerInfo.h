#pragma once

#include "../Core.h"

namespace CoreTrace {
	struct LogFormatToken {
		char formatToken;
		std::string value;
	};

	struct LoggerFormat {
		std::vector<LogFormatToken> textFormat;

		std::map<std::string, std::string> colourFormat;
	};
}
