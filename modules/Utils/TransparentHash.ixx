module;
#include <cstddef>
#include <string>
#include <string_view>
export module Natsuki.Utils.TransparentHash;

export namespace Natsuki {
    struct transparentHash {
        using is_transparent = void;

        template<class T>
        constexpr size_t operator()(T &&str) const {
            return std::hash<std::string_view>{}(str);
        }
    };

    struct transparentEqual {
        using is_transparent = void;

        template<class L, class R>
        constexpr bool operator()(L &&l, R &&r) const {
            return l == r;
        }
    };
}