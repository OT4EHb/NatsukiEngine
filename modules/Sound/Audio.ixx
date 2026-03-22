module;
#include <string_view>
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.Audio;
export import Natsuki.Sound.Mixer;

export namespace Natsuki {
	class Audio {
	private:
		MIX_Audio *audio{nullptr};
	public:
		Audio() = default;
		~Audio() {
			MIX_DestroyAudio(audio);
		}
		operator MIX_Audio *() {
			return audio;
		}

		bool load(std::string_view path, Mixer &mixer, bool predecode = true) {
			MIX_DestroyAudio(audio);
			audio = MIX_LoadAudio(mixer, path.data(), predecode);
			return audio != nullptr;
		}
	};
}