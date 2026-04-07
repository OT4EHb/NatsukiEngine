module;
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.Track;
export import Natsuki.Sound.Audio;
export import Natsuki.Utils.Properties;
export import Natsuki.Utils.View;

export namespace Natsuki {
	class Track {
	public:
		using NatsukiView = void;
	private:
		MIX_Track *track;
	public:
		class PlayBuild :public Properties {
		public:
			PlayBuild& loop(Sint64 loop) {
				set(MIX_PROP_PLAY_LOOPS_NUMBER, loop);
				return*this;
			}

			PlayBuild &maxFrame(Sint64 frame) {
				set(MIX_PROP_PLAY_MAX_FRAME_NUMBER, frame);
				return *this;
			}
			PlayBuild &maxMS(Sint64 milliseconds) {
				set(MIX_PROP_PLAY_MAX_MILLISECONDS_NUMBER, milliseconds);
				return *this;
			}

			PlayBuild &startFrame(Sint64 frame) {
				set(MIX_PROP_PLAY_START_FRAME_NUMBER, frame);
				return *this;
			}
			PlayBuild &startMS(Sint64 milliseconds) {
				set(MIX_PROP_PLAY_START_MILLISECOND_NUMBER, milliseconds);
				return *this;
			}

			PlayBuild &loopStartFrame(Sint64 frame) {
				set(MIX_PROP_PLAY_LOOP_START_FRAME_NUMBER, frame);
				return *this;
			}
			PlayBuild &loopStartMS(Sint64 milliseconds) {
				set(MIX_PROP_PLAY_LOOP_START_MILLISECOND_NUMBER, milliseconds);
				return *this;
			}

			PlayBuild &fadeInFrame(Sint64 frame) {
				set(MIX_PROP_PLAY_FADE_IN_FRAMES_NUMBER, frame);
				return *this;
			}
			PlayBuild &fadeInMS(Sint64 milliseconds) {
				set(MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, milliseconds);
				return *this;
			}
			PlayBuild &fadeInStartGain(float gain) {
				set(MIX_PROP_PLAY_FADE_IN_START_GAIN_FLOAT, gain);
				return *this;
			}

			PlayBuild &silenceFrame(Sint64 frame) {
				set(MIX_PROP_PLAY_APPEND_SILENCE_FRAMES_NUMBER, frame);
				return *this;
			}
			PlayBuild &silenceMS(Sint64 milliseconds) {
				set(MIX_PROP_PLAY_APPEND_SILENCE_MILLISECONDS_NUMBER, milliseconds);
				return *this;
			}

			/*PlayBuild& halt(bool stop) {
				set(MIX_PROP_PLAY_HALT_WHEN_EXHAUSTED_BOOLEAN, stop);
				return *this;
			}*/

			PlayBuild &startOrder(Sint64 order) {
				set(MIX_PROP_PLAY_START_ORDER_NUMBER, order);
				return *this;
			}
		};
		static View<Track> getFromRaw(MIX_Track *ptr) {
			View<Track> view;
			view->track = ptr;
			return view;
		}
		Track(Mixer &mixer) {
			track = MIX_CreateTrack(mixer.getRaw());
			checkCall(track != nullptr);
		}
		~Track() {
			MIX_DestroyTrack(track);
		}
		MIX_Track *getRaw() {
			return track;
		}

		bool setAudio(Audio &audio) {
			return MIX_SetTrackAudio(track, audio.getRaw());
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

		bool playing() const {
			return MIX_TrackPlaying(track);
		}
		bool paused() const {
			return MIX_TrackPaused(track);
		}
	};
}