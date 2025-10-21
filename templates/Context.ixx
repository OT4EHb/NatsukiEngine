export module Context;

export class Context {
private:
	Context();
public:
	static Context &get() {
		static Context context{};
		return context;
	}
};