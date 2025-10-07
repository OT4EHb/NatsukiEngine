#pragma once
#include <ostream>

class Loger {
private:
	static Loger loger;
	std::ostream *stream = nullptr;
	bool isTemp = false;
	Loger() = default;
	static void clear();
public:
	inline ~Loger();
	static void setStream(std::ostream &stream);
	static void setStream(const std::string &filename);
	static std::ostream &get();
};

Loger::~Loger() {
	clear();
}

#define LOGER (Loger::get())