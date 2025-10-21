export module CategoryLog;
export import Loger;
import <source_location>;

export class CategoryLog {
public:
	CategoryLog(const std::string_view &category,
				const std::source_location loc = std::source_location::current()) {
		Loger::get()
			<< "file: " << loc.file_name()
			<< '(' << loc.line() << ':' << loc.column() << ')'
			<< "\n`" << loc.function_name() << "`\n"
			<< category << ":\n";
	}
	~CategoryLog() {
		Loger::get() << '\n' << std::endl;
	}

	template<typename T>
	CategoryLog &operator<<(const T &value) {
		Loger::get() << value;
		return *this;
	}
};