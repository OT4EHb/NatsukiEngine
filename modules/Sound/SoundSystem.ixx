module;
#include <cstddef>
#include <cstdint>
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

		static void stopedTrack(void *data, MIX_Track *track) {
			SoundSystem *system = reinterpret_cast<SoundSystem *>(data);
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

		bool stopAll(Sint64 fade_out_ms = 0) {
			return mixer.stopAllTracks(fade_out_ms);
		}

		bool empty() {
			return freeTracks.empty();
		}

		View<Track> getFreeTrack() {
			if (empty()) throw Exception("All tracks are busy");
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