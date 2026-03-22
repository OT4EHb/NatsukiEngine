module;
#include <concepts>
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

		operator SDL_PropertiesID() const noexcept {
			return id;
		}

		Properties &operator=(const Properties &prop) {
			if (this != &prop) {
				checkCallSDL(SDL_CopyProperties(prop.id, id));
			}
			return *this;
		}
		Properties(const Properties &prop) :Properties() {
			checkCallSDL(SDL_CopyProperties(prop.id, id));
		}

		Properties &operator=(Properties &&prop)noexcept {
			std::swap(id, prop.id);
			return *this;
		}
		Properties(Properties &&prop)noexcept :id(prop.id) {
			prop.id = 0;
		}

		bool clear(const char *name) noexcept{
			return SDL_ClearProperty(id, name);
		}

		bool get(const char *name, bool default_value) const noexcept {
			return SDL_GetBooleanProperty(id, name, default_value);
		}
		Sint64 get(const char *name, Sint64 default_value) const noexcept {
			return SDL_GetNumberProperty(id, name, default_value);
		}
		float get(const char *name, float default_value) const noexcept {
			return SDL_GetFloatProperty(id, name, default_value);
		}
		void* get(const char *name, void* default_value) const noexcept {
			return SDL_GetPointerProperty(id, name, default_value);
		}
		const char* get(const char* name, const char* default_value) const noexcept {
			return SDL_GetStringProperty(id, name, default_value);
		}

		bool set(const char *name, bool value) noexcept {
			return SDL_SetBooleanProperty(id, name, value);
		}
		bool set(const char *name, Sint64 value)noexcept {
			return SDL_SetNumberProperty(id, name, value);
		}
		bool set(const char *name, float value) noexcept {
			return SDL_SetFloatProperty(id, name, value);
		}
		bool set(const char *name, void*value)noexcept {
			return SDL_SetPointerProperty(id, name, value);
		}
		bool set(const char* name, const char*value)noexcept {
			return SDL_SetStringProperty(id, name, value);
		}

		bool has(const char *name) const noexcept {
			return SDL_HasProperty(id, name);
		}

		bool lock() {
			return SDL_LockProperties(id);
		}

		void unlock() {
			SDL_UnlockProperties(id);
		}

		bool isValid() const noexcept {
			return id != 0;
		}
	};
}