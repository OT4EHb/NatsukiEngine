module;
#include <fstream>
module Natsuki.Loger;

using namespace Natsuki;

Loger Loger::loger;

void Loger::clear() {
	if (loger.isTemp) {
		loger.isTemp = false;
		delete loger.stream;
	}
}

void Loger::setStream(std::ostream &stream) {
	clear();
	loger.stream = &stream;
}

void Loger::setStream(const std::string &filename) {
	auto file = new std::ofstream(filename+".log");
	setStream(*file);
	loger.isTemp = true;
}