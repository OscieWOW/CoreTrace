#include "Logger.h"

namespace CoreTrace {
	void Logger::init() {
		m_outputSink = std::make_shared<Sinks::ConsoleSink>();
		m_outputSink->init(m_info);
		m_info.genFormat("[%N] %M");
	}

	Logger::Logger(LoggerInfo info):m_info(info) {
	}	
}
