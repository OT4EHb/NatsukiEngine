module;
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.Track;
export import Natsuki.Sound.Audio;
export import Natsuki.Utils.Properties;

export namespace Natsuki {
	class Track {
	private:
		MIX_Track *track;
	public:
		Track(Mixer &mixer) {
			track = MIX_CreateTrack(mixer);
			checkCallSDL(track != nullptr);
		}
		~Track() {
			MIX_DestroyTrack(track);
		}

		bool setAudio(Audio &audio) {
			return MIX_SetTrackAudio(track, audio);
		}

		bool setGain(float gain) {
			return MIX_SetTrackGain(track, gain);
		}
		float getGain() {
			return MIX_GetTrackGain(track);
		}

		bool setPlaybackPosition(Sint64 frames) {
			return MIX_SetTrackPlaybackPosition(track, frames);
		}
		Sint64 getPlaybackPosition() {
			return MIX_GetTrackPlaybackPosition(track);
		}

		bool play(SDL_PropertiesID prop = 0) {
			return MIX_PlayTrack(track, prop);
		}
		bool pause() {
			return MIX_PauseTrack(track);
		}
		bool resume() {
			return MIX_ResumeTrack(track);
		}
		bool stop(Sint64 fade_out_frames) {
			return MIX_StopTrack(track, fade_out_frames);
		}

		Sint64 MSToFrames(Sint64 ms) {
			return MIX_TrackMSToFrames(track, ms);
		}
		Sint64 FramesToMS(Sint64 frames) {
			return MIX_TrackFramesToMS(track, frames);
		}

	};
}