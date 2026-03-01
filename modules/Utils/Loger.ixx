module;
#include <concepts>
#include <fstream>
#include <source_location>
#include <string_view>
export module Natsuki.Utils.Loger;
export import Natsuki.Exception;

export namespace Natsuki {
	class Loger {
	public:
		enum class Level {
			DEBUG,
			INFO,
			WARNING,
			ERROR,
			CRITICAL
		};
	private:
		std::ostream *ostream{nullptr};
		Level minLevel{Level::DEBUG};
		bool isTemp{false};

		static constexpr const char *levelToString(Level level) {
			switch (level) {
				case Level::DEBUG:   return "DEBUG";
				case Level::INFO:    return "INFO";
				case Level::WARNING: return "WARNING";
				case Level::ERROR:   return "ERROR";
				case Level::CRITICAL:   return "CRITICAL";
				default: return "UNKNOWN";
			}
		}
	public:
		class Message {
		private:
			Loger &loger;
			bool should;
		public:
			Message(Loger &loger, Level lvl,
					const std::source_location &loc = std::source_location::current()):
				loger(loger) {
				should = lvl >= loger.minLevel;
				if (should) {
					loger << "[" << Loger::levelToString(lvl) << "] "
						<< "[" << loc.file_name() << ":" << loc.line() << ":"
						<< loc.function_name() << "] ";
				}
			}
			~Message() {
				if (should) {
					loger << std::endl;
				}
			}

			template<class T>
			Message &operator<<(const T &val) {
				if (should) {
					loger << val;
				}
				return *this;
			}

			Message &operator<<(std::ostream &(*manip)(std::ostream &)) {
				if (should) {
					loger << manip;
				}
				return *this;
			}

			Message(const Message &) = delete;
			Message &operator=(const Message &) = delete;
			Message(Message &&) = delete;
			Message &operator=(Message &&) = delete;
		};

		Loger() = delete;

		Loger(std::ostream &stream):
		ostream(&stream), isTemp(false){
		}

		Loger(const std::string &filename) {
			setStream(filename);
		}

		~Loger() {
			reset();
		}

		Loger(Loger &&other) noexcept
			: ostream(other.ostream), isTemp(other.isTemp) {
			other.ostream = nullptr;
			other.isTemp = false;
		}

		Loger &operator=(Loger &&other) noexcept {
			if (this != &other) {
				reset();
				ostream = other.ostream;
				isTemp = other.isTemp;
				other.ostream = nullptr;
				other.isTemp = false;
			}
			return *this;
		}

		void reset() {
			if (isTemp) {
				delete ostream;
				isTemp = false;
			}
			ostream = nullptr;
		}

		inline bool isValid() const {
			return ostream != nullptr;
		}

		bool isGood() const {
			return isValid() && ostream->good();
		}

		void setStream(std::ostream &stream) {
			reset();
			ostream = &stream;
			isTemp = false;
		}

		void setStream(const std::string &filename) {
			reset();
			std::ofstream *file = new std::ofstream(filename + ".log");
			if (!file->is_open()) {
				delete file;
				throw Exception("Cannot open log file: " + filename);
			}
			ostream = file;
			isTemp = true;
		}

		void setLevel(Level lvl) {
			minLevel = lvl;
		}

		template<class T>
		requires !std::convertible_to<T,std::string_view>
		Loger &operator<<(const T &val) {
			if (isGood()) {
				*ostream << val;
			}
			return *this;
		}

		Loger &operator<<(std::string_view str) {
			if (isGood()) {
				*ostream << str;
			}
			return *this;
		}

		Loger &operator<<(std::ostream &(*manip)(std::ostream &)) {
			if (isGood()) {
				manip(*ostream);
			}
			return *this;
		}

		Message log(Level level, const std::source_location &loc = std::source_location::current()) {
			return Message(*this, level, loc);
		}
	};
}