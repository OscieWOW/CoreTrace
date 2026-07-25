#include <CoreTrace.h>

int main() {
	std::shared_ptr<CoreTrace::Logger> log = std::make_shared<CoreTrace::Logger>("CORE");
	
	auto sink = std::make_shared<CoreTrace::Sinks::UFileSink>("CORE");
	
	log->init(sink, "NONE");
	
	log->setFormat("myFormat","<%N, %M>%", "NONE");
	
	log->trace("Trace");
	log->message("Message");
	log->warning("Warning");
	log->fatal("Fatal");
	log->log("myFormat", "myFormat");

	return 0;
}
