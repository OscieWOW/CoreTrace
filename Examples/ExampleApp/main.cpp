#include <CoreTrace.h>

int main() {
	std::shared_ptr<CoreTrace::Logger> log = std::make_shared<CoreTrace::Logger>("CORE-SINK");
	
	auto sink = std::make_shared<CoreTrace::Sinks::UConsoleSink>("CORE-CONSOLE");
	
	log->init(sink);
	
	log->trace("Trace");
	log->message("Message");
	log->warning("Warning");
	log->fatal("Fatal");

	return 0;
}
