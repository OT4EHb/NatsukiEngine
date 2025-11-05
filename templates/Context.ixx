export module Context;

export class Context {
private:
	Context();
public:
	Context(Context &) = delete;
	Context(Context &&) = delete;
	static Context &get() {
		static Context context{};
		return context;
	}
};