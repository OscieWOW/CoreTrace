#include <CoreTrace.h>

int main() {
	CoreTrace::LoggerInfo info = {
		.debugName = "CORE",
		.includeName = true,
	};
	CoreTrace::Logger log = CoreTrace::Logger(info);
	log.init();

	log.trace("Trace numer:{} ",16);
	log.message("Message string: {}", "hello");
	log.warning("Warning float:{}",3.14);
	log.fatal("Fatal char:{}", 'p');
	return 0;
}
