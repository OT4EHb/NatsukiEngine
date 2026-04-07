module;
#include <string_view>
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.Audio;
export import Natsuki.Sound.Mixer;

export using ::Sint64;

export namespace Natsuki {
	class Audio {
	private:
		MIX_Audio *audio{nullptr};

		Audio(MIX_Audio *raw) {
			audio = raw;
		}
	public:
		Audio() = default;
		~Audio() {
			MIX_DestroyAudio(audio);
		}
		MIX_Audio *getRaw() {
			return audio;
		}

		bool isValid() {
			return audio != nullptr;
		}

		bool load(std::string_view path, Mixer &mixer, bool predecode = true) {
			MIX_DestroyAudio(audio);
			audio = MIX_LoadAudio(mixer.getRaw(), path.data(), predecode);
			return audio != nullptr;
		}

		static Audio createSineWave(Mixer &mixer, int hz, float amplitude, Sint64 ms) {
			MIX_Audio *raw = MIX_CreateSineWaveAudio(mixer.getRaw(), hz, amplitude, ms);
			checkCall(raw != nullptr);
			return Audio(raw);
		}
	};
}