#pragma once

#include "Sink.h"

namespace CoreTrace::Sinks {
	class UConsoleSink:public USink {
		public:
			UConsoleSink() = default;

			void fatal(std::string message) override {
				std::cout << message << std::endl;
			}

			void warning(std::string message) override {
				std::cout << message << std::endl;
			}

			void message(std::string message) override {
				std::cout << message << std::endl;
			}

			void trace(std::string message) override {
				std::cout << message << std::endl;
			}

			void log(std::string message) override {
				std::cout << message << std::endl;
			}
	};

	class SConsoleSink: public SSink {
		public:
			void log(const Node& node) override {
				printNode(node, 0);
			}

			void printNode(const Node& node, int depth) {
				if(depth == 0) {
					std::cout << "Name: " << node.name << std::endl;
					std::cout << "|-> Type: " << node.type << std::endl;
					std::cout << "|-> Value: " << node.value << std::endl;
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
					std::cout << margin.str() << "-> Name: " << node.name << std::endl;
					std::cout << margin.str() << "   |-> Type: " << node.type << std::endl;
					std::cout << margin.str() << "   |-> Value: " << node.value << std::endl;
					std::cout << margin.str() << "   |-> Depth: " << depth << std::endl;
					if(node.childNodes.size() > 0) {
						for(Node childNode:node.childNodes) {
							printNode(childNode, depth+1);
						}
					}
				}
			}
	};
}
