#pragma once

#include "../Core.h"

namespace CoreTrace {	
	struct Node {
		std::vector<Node> childNodes;
		
		std::string name = "";
		std::string type = "";
		std::string value = "";
	};

	struct DebugEvent {
		int eventID;
		std::string functionName;
		int parentProcess;
		std::vector<Node> functionParameters;
		std::optional<Node> functionReturn;
		std::chrono::time_point<std::chrono::system_clock> functionStart;
		std::chrono::time_point<std::chrono::system_clock> functionEnd;
		std::string functionSuccess;

		
	};


}
