#pragma once

#include <CoreTrace.h>
#include "Person.h"

class TypeSerialise : public CoreTrace::Serialise {
	public:
		using CoreTrace::Serialise::passParameter;
		CoreTrace::Node passParameter(Person paramValue, const std::string& paramName) {
			CoreTrace::Node node = {
				.childNodes = {passParameter(paramValue.age, "age"),passParameter(paramValue.name, "name"), passParameter(paramValue.likes, "likes"), passParameter(paramValue.dislikes, "dislikes"), passParameter(paramValue.gender, "gender")},
				.name = paramValue.name,
				.type = "PERSON"
			};
			return node;
		}
};
