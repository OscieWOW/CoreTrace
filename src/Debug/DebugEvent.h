#pragma once

#include "../Core.h"
#include "Serialise.h"

namespace CoreTrace {
	struct DebugEvent {
		int eventID;
		std::string functionName;
		int parentProcess;
		std::vector<Node> functionParameters;
		std::chrono::time_point<std::chrono::system_clock> functionStart;
		std::chrono::time_point<std::chrono::system_clock> functionEnd;
		std::string functionSuccess;

		
	};
}
