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
					m_file.open(fileName.str(), std::ios::in|std::ios::out|std::ios::trunc);
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
					m_file.open(file.str(), std::ios::in|std::ios::out|std::ios::trunc);

					if(!m_file.is_open()) {
						std::cout << "failed to open file " << file.str() << std::endl;
						exit(-1);
					}
				}

				void setPath(const std::string& path) {
					m_filePath = path;
				}

				void log(const Node& node) override {
					m_file << node.name << std::endl; 
				}

			protected:
				std::fstream m_file = std::fstream();
				std::string m_fileName = "";
				std::string m_filePath = "";
		};
	}
}
