#include <CoreTrace.h>

int main() {
	CoreTrace::LoggerInfo info = {
		.debugName = "CORE",
		.includeName = true,
	};
	CoreTrace::Logger log = CoreTrace::Logger(info);
	log.init();
	log.trace("Hi {}", 5);
	return 0;
}
