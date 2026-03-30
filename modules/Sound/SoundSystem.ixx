module;
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <type_traits>
#include <vector>
#include <SDL3_mixer/SDL_mixer.h>
export module Natsuki.Sound.SoundSystem;
export import Natsuki.Sound.Track;
export import Natsuki.Exception;

export using ::uint32_t;

export namespace Natsuki {
	class SoundSystem {
	private:
		static constexpr size_t SIZE = 32;
		Mixer mixer;
		std::vector<Track> tracks;
		std::vector<MIX_Track*>freeTracks;
		std::mutex mutex;

		static void stopedTrack(void *data, MIX_Track *track) {
			SoundSystem *system = reinterpret_cast<SoundSystem *>(data);
			auto guard = std::lock_guard(system->mutex);
			system->freeTracks.push_back(track);
		}
	public:
		explicit SoundSystem():mixer() {
			tracks.reserve(SIZE);
			freeTracks.resize(SIZE);
			for (size_t i{}; i < SIZE; ++i) {
				auto &track = tracks.emplace_back(std::ref(mixer));
				freeTracks[SIZE - 1 - i] = static_cast<MIX_Track *>(track);
			}
		}
		~SoundSystem() = default;

		void stopAll(Sint64 fade_out_ms = 0) {
			auto guard = std::lock_guard(mutex);
			mixer.stopAllTracks(fade_out_ms);
			freeTracks.clear();
			for (size_t i{}; i < SIZE; ++i) {
				freeTracks[SIZE - 1 - i] = static_cast<MIX_Track *>(tracks[i]);
			}
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
	};
}