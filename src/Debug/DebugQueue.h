#pragma once

#include "../Core.h"
#include "../Core/Logger.h"
#include "Serialise.h"
#include "DebugEvent.h"

namespace CoreTrace {
	template <class Serialiser = Serialise>
	class DebugQueue {
		public:
			DebugQueue(std::shared_ptr<Logger> logger, Serialiser parameterPasser = Serialise{}):m_logger(logger),m_parameterPasser(std::move(parameterPasser)) {};
			
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
				
				m_logger->trace("function {} eventID:{}",m_events[fnID].functionName, m_events[fnID].eventID);
				m_logger->trace("Event duration:{} microseconds",duration.count());
				for(Node param:m_events[fnID].functionParameters) {
					printNode(param, 0);
				}
				if(m_events[fnID].functionReturn) {
					m_logger->trace("Return Value: {}", (*m_events[fnID].functionReturn).name);
					m_logger->trace("|-> Type: {}", (*m_events[fnID].functionReturn).type);
					m_logger->trace("|-> Value: {}", (*m_events[fnID].functionReturn).value);
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

			void printNode(Node node, int depth) {
				if(depth == 0) {
					m_logger->trace("Name: {}", node.name);
					m_logger->trace("|-> Type: {}", node.type);
					m_logger->trace("|-> Value: {}", node.value);
					if(node.childNodes.size() > 0) {
						for(Node childNode:node.childNodes) {
							printNode(childNode, depth+1);
						}
					}
				} else {
					std::stringstream margin;
					margin << "|";
					for(int i = 0; i < depth; i++) {
						margin << "   |";
					}
					m_logger->trace("{}-> Name: {}",margin.str(), node.name);
					m_logger->trace("{}   |-> Type: {}", margin.str(), node.type);
					m_logger->trace("{}   |-> Value: {}", margin.str(), node.value);
					m_logger->trace("{}   |-> Depth: {}", margin.str(), depth);
					if(node.childNodes.size() > 0) {
						for(Node childNode:node.childNodes) {
							printNode(childNode, depth+1);
						}
					}
				}
			}

		private:
			std::shared_ptr<Logger> m_logger;
			std::vector<DebugEvent> m_events;
			Serialiser m_parameterPasser;
	};
}
