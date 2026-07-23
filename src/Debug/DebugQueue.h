#pragma once

#include "../Core.h"
#include "../Core/Logger.h"
#include "Serialise.h"
#include "DebugEvent.h"

namespace CoreTrace {
	template <class Serialiser = Serialise>
	class DebugQueue {
		public:
			DebugQueue(std::shared_ptr<Sinks::SSink> logger, Serialiser parameterPasser = Serialise{}):m_logger(logger),m_parameterPasser(std::move(parameterPasser)) {};
			
			int functionStart(std::string name, int parentProcessID) {
				DebugEvent e;
				e.eventID = m_events.size();
				e.functionName = name;
				e.parentProcess = parentProcessID;
				e.functionStart = std::chrono::system_clock::now();

				m_events.push_back(e);

				return e.eventID;
			}

			void functionEnd(int fnID) {
				m_events[fnID].functionSuccess = true;
				m_events[fnID].functionEnd = std::chrono::system_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(m_events[fnID].functionEnd - m_events[fnID].functionStart);
				
				const DebugEvent fnE = m_events[fnID];
				const Node returnVal = m_parameterPasser.passParameter(fnE, "ReturnValue");
				m_logger->log(returnVal);
				for(Node param:m_events[fnID].functionParameters) {
					m_logger->log(param);
				}
				if(m_events[fnID].functionReturn) {
					m_logger->log(*m_events[fnID].functionReturn);
				}
			}
			
			template <typename T>
			void addParameter(int fnID, T parameter, const std::string& paramName) {
				Node param = m_parameterPasser.passParameter(parameter, paramName);
				m_events[fnID].functionParameters.push_back(param);

			}

			template <typename T>
			void addFunctionReturn(int fnID, T parameter, const std::string& paramName) {
				Node returnNode = m_parameterPasser.passParameter(parameter, paramName);
				m_events[fnID].functionReturn = returnNode;
			}

		private:
			std::shared_ptr<Sinks::SSink> m_logger;
			std::vector<DebugEvent> m_events;
			Serialiser m_parameterPasser;
	};
}
