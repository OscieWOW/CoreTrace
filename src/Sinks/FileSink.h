#pragma once

#include "Sink.h"
#include "../Core.h"

namespace CoreTrace {
	namespace Sinks{
		class UFileSink: public USink {
			public:
				UFileSink(const std::string& name):USink(name),m_fileName(name)  {}
				~UFileSink() {
					m_file.close();
				}

				void init() {
					std::stringstream fileName;
					fileName << m_filePath << m_fileName;
					fileName << ".txt";
					m_file.open(fileName.str(), std::ios::out|std::ios::trunc);
					if(!m_file.is_open()) {
						std::cout << "failed to open file " << fileName.str() << std::endl;
						exit(-1);
					}

				}

				void fatal(const std::string& message) override {
					m_file << message << std::endl;					
				}

				void warning(const std::string& message) override {
					m_file << message << std::endl;					
				}

				void message(const std::string& message) override {
					m_file << message << std::endl;					
				}

				void trace(const std::string& message) override {
					m_file << message << std::endl;					
				}

				void log(const std::string& message) override {
					m_file << message << std::endl;	
				}

			protected:
				std::fstream m_file = std::fstream();
				std::string m_filePath = "";
				std::string m_fileName;
		};

		class SFileSink: public SSink {
			public:
				SFileSink(const std::string& name):SSink(name), m_fileName(name) {}

				~SFileSink() {
					m_file.close();
				}

				void init() override {
					std::stringstream file;
					file << m_filePath;
					file << m_fileName;
					file << ".txt";
					m_file.open(file.str(), std::ios::out|std::ios::trunc);

					if(!m_file.is_open()) {
						std::cout << "failed to open file " << file.str() << std::endl;
						exit(-1);
					}
				}

				void setPath(const std::string& path) {
					m_filePath = path;
				}

				/*
				void log(const Node& node) override {
					std::vector<int> layerDepth = {};
					//the index is the depth and the value is the index of the next node from the currently processed node
					
					int tempI = 0;

					bool isntEnd = true;
					int currentDepth = 0;
					Node currentNode = node;
					int i = 0;
					int maxIndex = 0;

					std::cout << node.name << std::endl;
					
					while(isntEnd && tempI <= 150) {
						if(currentDepth == 0) {
							m_file << "Name: " << node.name << std::endl;
							m_file << "|-> Type: " << node.type << std::endl;
							m_file << "|-> Value: " << node.value << std::endl;

							if(node.childNodes.size() > 0) {
								currentDepth = 1;
							}
						} else {
							std::stringstream margin;
							margin << "|";
							for(int index = 0; index < currentDepth; index++) {
								margin << "   |";
							}
							
							Node parentNode = node;
							for(int j = 0; j<currentDepth-1;j++) {
								parentNode = parentNode.childNodes[layerDepth[j]];
							}

							for(i = 0;i<parentNode.childNodes.size();i++) {
								m_file << margin.str() << "-> Name: " << parentNode.childNodes[i].name;
								if(parentNode.childNodes[i].childNodes.size() > 0) {
									currentDepth++;
									layerDepth.push_back(i);
								}
							}
						}
						tempI++;
					}
				}
				*/

				void log(const Node& node) override {
					printNode(node, 0);
				}

				void printNode(const Node& node, int depth) {
					if(depth == 0) {
						m_file << "Name: " << node.name << std::endl;
						m_file << "|-> Type: " << node.type << std::endl;
						m_file << "|-> Value: " << node.value << std::endl;
						
						if(node.childNodes.size() > 0) {
							for(const Node& childNode:node.childNodes) {
								printNode(childNode, 1);
							}
						}
					} else {
						std::stringstream margin;
						margin << "|";
						for(int i = 0; i < depth; i++) {
							margin << "   |";
						}
						m_file << margin.str() << "-> Name: " << node.name << std::endl;
						m_file << margin.str() << "   |-> Type: " << node.type << std::endl;
						m_file << margin.str() << "   |-> Value: " << node.value << std::endl;

						if(node.childNodes.size() > 0) {
							for(const Node& childNode:node.childNodes) {
								printNode(childNode, depth+1);
							}
						}
					}
				}

			protected:
				std::fstream m_file = std::fstream();
				std::string m_fileName = "";
				std::string m_filePath = "";
		};
	}
}
