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
	~Loger();
	static void setStream(std::ostream &stream);
	static void setStream(const std::string &filename);
	static std::ostream &get();
};

#define LOGER (Loger::get())