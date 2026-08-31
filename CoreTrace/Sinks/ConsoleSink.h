#pragma once

#include "Sink.h"

namespace CoreTrace::Sinks {
	class UConsoleSink:public USink {
		public:
			UConsoleSink(const std::string& name):USink(name) {}

			void init() {}

			void fatal(const std::string& message) override {
				std::cout << message << std::endl;
			}

			void warning(const std::string& message) override {
				std::cout << message << std::endl;
			}

			void message(const std::string& message) override {
				std::cout << message << std::endl;
			}

			void trace(const std::string& message) override {
				std::cout << message << std::endl;
			}

			void log(const std::string& message) override {
				std::cout << message << std::endl;
			}
	};

	class SConsoleSink: public SSink {
		public:
			SConsoleSink(const std::string& name):SSink(name) {}

			void log(const Node& node) override {
				printNode(node, 0);
			}

			void init () {}

			void printNode(const Node& node, int depth) {
				if(depth == 0) {
					if(node.name != "") std::cout << "Name: " << node.name << std::endl;
					if(node.type != "") std::cout << "|-> Type: " << node.type << std::endl;
					if(node.value != "") std::cout << "|-> Value: " << node.value << std::endl;
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
					if(node.name != "") std::cout << margin.str() << "-> Name: " << node.name << std::endl;
					if(node.type != "") std::cout << margin.str() << "   |-> Type: " << node.type << std::endl;
					if(node.value != "") std::cout << margin.str() << "   |-> Value: " << node.value << std::endl;
					if(node.childNodes.size() > 0) {
						for(Node childNode:node.childNodes) {
							printNode(childNode, depth+1);
						}
					}
				}
			}
	};
}
