export module Velocity;
export import Component;

export struct Velocity {
	float dx;
	float dy;
};

export template<>
struct traitComponent<Velocity> :std::true_type {};