export module CategoryLog;
export import Loger;

export class CategoryLog {
public:
	CategoryLog(const std::string &category) {
		Loger::get() << category << ":\t";
	}
	~CategoryLog() {
		Loger::get() <<'\n' << std::endl;
	}

	template<typename T>
	CategoryLog &operator<<(const T &value) {
		Loger::get() << value;
		return *this;
	}
};