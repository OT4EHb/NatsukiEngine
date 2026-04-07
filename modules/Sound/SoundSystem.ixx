module;
#include <cstddef>
#include <mutex>
#include <type_traits>
#include <vector>
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.SoundSystem;
export import Natsuki.Sound.Track;
export import Natsuki.Exception;

export using ::size_t;

export namespace Natsuki {
	class SoundSystem {
	private:
		Mixer mixer;
		std::vector<Track> tracks;
		std::vector<MIX_Track*>freeTracks;
		std::mutex mutex;

		static void stopedTrack(void *data, MIX_Track *track) {
			SoundSystem *system = reinterpret_cast<SoundSystem *>(data);
			auto guard=std::lock_guard(system->mutex);
			system->freeTracks.push_back(track);
		}
	public:
		explicit SoundSystem(size_t trackCount):mixer() {
			tracks.reserve(trackCount);
			freeTracks.resize(trackCount);
			for (size_t i{}; i < trackCount; ++i) {
				auto &track = tracks.emplace_back(std::ref(mixer));
				freeTracks[trackCount - 1 - i] = track.getRaw();
			}
		}
		~SoundSystem() = default;

		bool stopAll(Sint64 fade_out_ms = 0) {
			return mixer.stopAllTracks(fade_out_ms);
		}

		bool hasFreeTrack() {
			auto guard = std::lock_guard(mutex);
			return !freeTracks.empty();
		}

		View<Track> getFreeTrack() {
			auto guard = std::lock_guard(mutex);
			if (freeTracks.empty()) throw Exception("All tracks are busy");
			auto back = freeTracks.back();
			auto view = Track::getFromRaw(back);
			MIX_SetTrackStoppedCallback(back, stopedTrack, this);
			freeTracks.pop_back();
			return view;
		}

		Mixer &getMixer() {
			return mixer;
		}
	};
}