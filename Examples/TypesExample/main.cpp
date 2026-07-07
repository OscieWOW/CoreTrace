#include <CoreTrace.h>
#include "TypeSerialise.h"

void greet(std::shared_ptr<CoreTrace::DebugQueue<TypeSerialise>> q, Person person) {
	int fnID = q->functionStart("greet",0);
	q->addParameter(fnID, person, "person");

	std::cout << person.name << " says hi." << std::endl;

	q->functionEnd(fnID);
}

int main() {
	std::shared_ptr<CoreTrace::Logger> logger = std::make_shared<CoreTrace::Logger>("TYPE-EXAMPLE");
	logger->init();
	std::shared_ptr<CoreTrace::DebugQueue<TypeSerialise>> q = std::make_shared<CoreTrace::DebugQueue<TypeSerialise>>(logger, TypeSerialise{});

	Person person = {
		.age = 16,
		.name = "Oscar",
		.likes = {"C++", "C"},
		.dislikes = {"Other people", "Errors"},
		.gender = "Male"
	};

	greet(q, person);
	
	return 0;
}
