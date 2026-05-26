#pragma once

#include "../Core.h"
#include "../Core/Logger.h"
#include "Serialise.h"
#include "DebugEvent.h"

namespace CoreTrace {
	class DebugQueue {
		public:
			DebugQueue(std::shared_ptr<Logger> logger):m_logger(logger) {
				m_parameterPasser.setName(m_logger->getName());
			};
			
			int functionStart(std::string name, int parentProcessID) {
				DebugEvent e;
				e.eventID = m_events.size();
				e.functionName = name;
				e.parentProcess = parentProcessID;
				e.functionStart = std::chrono::system_clock::now();

				m_events.push_back(e);

				return e.eventID;
			}

			void functionEnd(int eventID) {
				m_events[eventID].functionSuccess = true;
				m_events[eventID].functionEnd = std::chrono::system_clock::now();

				m_logger->trace("{} eventID:{}",m_events[eventID].functionName, m_events[eventID].eventID);
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(m_events[eventID].functionEnd - m_events[eventID].functionStart);

				m_logger->trace("Event duration:{}",duration.count());
			}
			
			template <typename T>
			void addParameter(T parameter, const std::string& paramName) {
				m_parameterPasser.addParameter(parameter, paramName);
			}

		private:
			std::shared_ptr<Logger> m_logger;
			std::vector<DebugEvent> m_events;
			Serialise m_parameterPasser;
	};
}
