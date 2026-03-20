module;
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.Mixer;
export import Natsuki.Exception;

export namespace Natsuki {
	class Mixer {
	private:
		MIX_Mixer *mixer;
	public:
		Mixer() {
			mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
			checkCallSDL(mixer != nullptr);
		}
		~Mixer() {
			MIX_DestroyMixer(mixer);
		}
	};
}