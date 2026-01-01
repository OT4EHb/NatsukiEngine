module;
#include <concepts>
export module System;

export class System {};

export template<class T>
concept SystemType = std::is_base_of_v<System, T>;