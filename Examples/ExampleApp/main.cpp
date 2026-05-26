#include <CoreTrace.h>

int add(std::shared_ptr<CoreTrace::DebugQueue> dqueue, int num1, int num2) {
	int fnID = dqueue->functionStart("add" ,0);
	

	int sum = num1 + num2;

	dqueue->functionEnd(fnID);
	return sum;
}

int main() {
	std::shared_ptr<CoreTrace::Logger> log = std::make_shared<CoreTrace::Logger>("CORE");
	log->init();
	
	log->setFormat("myFormat","%r%M");
	
	std::shared_ptr<CoreTrace::DebugQueue> dqueue = std::make_shared<CoreTrace::DebugQueue>(log);

	add(dqueue, 2, 100);
	return 0;
}
