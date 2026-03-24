module;
#include <cstdint>
#include <type_traits>
#include <vector>
export module Natsuki.Sound.SoundSystem;
export import Natsuki.Sound.Track;

export using ::uint32_t;

export namespace Natsuki {
	class SoundSystem {
	public:
		struct TrackID {
			uint32_t gen : 24;
			uint32_t id : 8;
			bool operator==(const TrackID &other)const {
				return gen == other.gen
					&& id == other.id;
			}
		};
	private:
		static constexpr size_t SIZE = 32;
		Mixer mixer;
		std::vector<Track> tracks;
		std::vector<TrackID>indices;
	public:
		explicit SoundSystem() {
			tracks.reserve(SIZE);
			indices.reserve(SIZE);
			for (size_t i{}; i <= SIZE; ++i) {
				tracks.emplace_back(std::ref(mixer));
				indices.emplace_back(0, i);
			}			
		}
		~SoundSystem() = default;

		TrackID getFreeTrack() {
			//
			return {0, 0};
		}
	};
}