#include <CoreTrace.h>

int main() {
	CoreTrace::Logger log = CoreTrace::Logger("CORE");
	log.init();
	
	log.setFormat("myFormat","%r%M");
	
	log.log("myFormat","My custom format");
	log.log("notAFormat","This is not a custom format so defaults to msgFormat");
	log.trace("Trace numer:{} ",16);
	log.message("Message string: {}", "hello");
	log.warning("Warning float:{}",3.14);
	log.fatal("Fatal char:{}", 'p');
	return 0;
}
