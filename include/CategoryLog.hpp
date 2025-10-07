#pragma once
#include <Loger.hpp>

class CategoryLog {
public:
	CategoryLog(const std::string &category) {
		LOGER << category << ":\n";
	}
	~CategoryLog() {
		LOGER <<'\n' << std::endl;
	}

	template<typename T>
	CategoryLog &operator<<(const T &value) {
		LOGER << value;
		return *this;
	}
};

#define DETAILED_LOG "File: " << __FILE__ << "\n"\
<< "Line: " << __LINE__ << "\n"

#define DEBUG_LOG CategoryLog("DEBUG")<<DETAILED_LOG
#define WARNING_LOG CategoryLog("WARNING")<<DETAILED_LOG
#define MESSAGE_LOG CategoryLog("MESSAGE")<<DETAILED_LOG
#define INFO_LOG CategoryLog("INFO")<<DETAILED_LOG