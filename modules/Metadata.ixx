module;
#include <string_view>
#include <SDL3/SDL_init.h>
export module Natsuki.Metadata;

export namespace Natsuki {
	class Metadata {
	private:
		static inline bool set(const char *name, const char *value) {
			return SDL_SetAppMetadataProperty(name, value);
		}

		static inline const char* get(const char *name) {
			return SDL_GetAppMetadataProperty(name);
		}
	public:
		Metadata() = delete;

		static bool setAppName(std::string_view name) {
			return set(SDL_PROP_APP_METADATA_NAME_STRING, name.data());
		}
		static const char *getAppName() {
			return get(SDL_PROP_APP_METADATA_NAME_STRING);
		}

		static bool setVersion(std::string_view version) {
			return set(SDL_PROP_APP_METADATA_VERSION_STRING, version.data());
		}
		static const char *getVersion() {
			return get(SDL_PROP_APP_METADATA_VERSION_STRING);
		}

		static bool setIdentifier(std::string_view identifier) {
			return set(SDL_PROP_APP_METADATA_IDENTIFIER_STRING, identifier.data());
		}
		static const char *getIdentifier() {
			return get(SDL_PROP_APP_METADATA_IDENTIFIER_STRING);
		}

		static bool setCreator(std::string_view creator) {
			return set(SDL_PROP_APP_METADATA_CREATOR_STRING, creator.data());
		}
		static const char *getCreator() {
			return get(SDL_PROP_APP_METADATA_CREATOR_STRING);
		}

		static bool setCopyright(std::string_view copyright) {
			return set(SDL_PROP_APP_METADATA_COPYRIGHT_STRING, copyright.data());
		}
		static const char *getCopyright() {
			return get(SDL_PROP_APP_METADATA_COPYRIGHT_STRING);
		}

		static bool setURL(std::string_view url) {
			return set(SDL_PROP_APP_METADATA_URL_STRING, url.data());
		}
		static const char *getURL() {
			return get(SDL_PROP_APP_METADATA_URL_STRING);
		}

		static bool setType(std::string_view type) {
			return set(SDL_PROP_APP_METADATA_TYPE_STRING, type.data());
		}
		static const char *getType() {
			return get(SDL_PROP_APP_METADATA_TYPE_STRING);
		}
	};
}