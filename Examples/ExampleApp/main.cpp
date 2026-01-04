#include <CoreTrace.h>

int main() {
	CoreTrace::LoggerInfo info = {
		.debugName = "CORE",
		.includeName = true,
	};
	info.genFormat("[%N] %M");
	CoreTrace::Logger log = CoreTrace::Logger(info);
	log.trace("Hi {}", 5);
	return 0;
}
