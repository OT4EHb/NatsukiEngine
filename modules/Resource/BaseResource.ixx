module;
#include <string_view>
export module Natsuki.Resource.BaseResource;

export namespace Natsuki {
	template<class R, class... Args>
	concept ResourceCheck = std::default_initializable<R>
		&& requires(R res, std::string_view path, Args&&... args) {
			{ res.load(path, std::forward<Args>(args)...) }
			-> std::same_as<bool>;
	};
}