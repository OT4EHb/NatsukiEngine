module;
#include <ostream>
#include <source_location>
export module Natsuki.Loger;

export namespace Natsuki {
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
		inline static std::ostream &get();
	};

	class CategoryLog {
	public:
		CategoryLog(std::string_view,
					const std::source_location = std::source_location::current());
		~CategoryLog();
		template<typename T>
		CategoryLog &operator<<(const T &);
	};
}

using namespace Natsuki;

Loger::~Loger() {
	clear();
}

std::ostream &Loger::get() {
	return *loger.stream;
}

CategoryLog::CategoryLog(std::string_view category,
			const std::source_location loc) {
	Loger::get()
		<< "file: " << loc.file_name()
		<< '(' << loc.line() << ':' << loc.column() << ')'
		<< "\n`" << loc.function_name() << "`\n"
		<< category << ":\n";
}
CategoryLog::~CategoryLog() {
	Loger::get() << '\n' << std::endl;
}

template<typename T>
CategoryLog &CategoryLog::operator<<(const T &value) {
	Loger::get() << value;
	return *this;
}