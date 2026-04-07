module;
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.Mixer;
export import Natsuki.Exception;

export using ::Sint64;
export using ::SDL_AudioDeviceID;
export using ::SDL_AudioSpec;

export namespace Natsuki {
	class Mixer {
	private:
		MIX_Mixer *mixer;
	public:
		Mixer(SDL_AudioDeviceID id = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, 
			  const SDL_AudioSpec *spec = nullptr) {
			mixer = MIX_CreateMixerDevice(id, spec);
			checkCall(mixer != nullptr);
		}
		~Mixer() {
			MIX_DestroyMixer(mixer);
		}
		MIX_Mixer *getRaw() {
			return mixer;
		}

		bool setGain(float gain) {
			return MIX_SetMixerGain(mixer, gain);
		}
		float getGain() {
			return MIX_GetMixerGain(mixer);
		}

		bool pauseAllTracks() {
			return MIX_PauseAllTracks(mixer);
		}
		bool resumeAllTracks() {
			return MIX_ResumeAllTracks(mixer);
		}

		bool stopAllTracks(Sint64 fade_out_ms = 0) {
			return MIX_StopAllTracks(mixer, fade_out_ms);
		}
	};
}