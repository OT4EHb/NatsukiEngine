#include <Loger.hpp>
#include <fstream>

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

std::ostream &Loger::get() {
	return *loger.stream;
}