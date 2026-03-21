module;
#include <SDL3/SDL_properties.h>
export module Natsuki.Utils.Properties;
export import Natsuki.Exception;

export using ::SDL_PropertiesID;

export namespace Natsuki {
	class Properties {
	private:
		SDL_PropertiesID id;
	public:
		Properties() {
			id = SDL_CreateProperties();
			checkCallSDL(id != 0);
		}
		~Properties() {
			SDL_DestroyProperties(id);
		}

		Properties& operator=(const Properties &prop) {
			checkCallSDL(SDL_CopyProperties(prop.id, id));
			return *this;
		}
		Properties(const Properties &prop) :Properties() {
			*this = prop;
		}

		Properties &operator=(Properties &&prop)noexcept {
			if (this != &prop) {
				id = prop.id;
				prop.id = 0;
			}
			return *this;
		}
		Properties(Properties &&prop)noexcept :id(prop.id) {
			prop.id = 0;
		}

		bool clear(const char *name) {
			return SDL_ClearProperty(id, name);
		}

		template<typename T>
		T get(const char *name, T defaults) {
			return defaults;
		}

	};
}