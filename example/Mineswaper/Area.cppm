module;
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
export module Area;
import Natsuki.Render.Renderer;

enum class TileState {
	HIDDEN,
	REVEALED,
	FLAGGED
};

struct Tile {
	unsigned nearbyMines = 0;
	TileState state = TileState::HIDDEN;
	bool isMine = 0;
};

export{
	enum class Result {
		NONE,
		WIN,
		LOSE
	};

	class Area {
	private:
		std::vector<std::vector<Tile>>data;
		size_t width;
		size_t height;
		size_t totalMine;
		std::mt19937 rng;
		Natsuki::Texture texture;
		size_t hidden;
		size_t mines;

		bool isValid(int i, int j) const {
			return i >= 0 && i < static_cast<int>(height) &&
				j >= 0 && j < static_cast<int>(width);
		}

		void setMine(size_t i, size_t j) {
			data[i][j].isMine = true;
			for (int di = -1; di <= 1; ++di) {
				for (int dj = -1; dj <= 1; ++dj) {
					if (di == 0 && dj == 0) continue;

					int ni = static_cast<int>(i) + di;
					int nj = static_cast<int>(j) + dj;

					if (isValid(ni, nj)) {
						data[ni][nj].nearbyMines++;
					}
				}
			}
		}

		void setTotalMine(size_t mine) {
			size_t limit = width * height * 0.4;
			totalMine = std::min(mine, limit);
			mines = totalMine;
		}
	public:
		Area(size_t width, size_t height, size_t mine, Natsuki::Renderer &ren) :
			width(width), height(height) {

			texture.load("res/minesweeper.png", ren.getRaw());
			setTotalMine(mine);
			std::random_device rd;
			rng.seed(rd());
			reset();
		}

		void reset() {
			data.assign(height, std::vector<Tile>(width));

			hidden = width * height;
			std::vector<size_t> indices(hidden);
			std::iota(indices.begin(), indices.end(), 0);
			std::shuffle(indices.begin(), indices.end(), rng);

			for (size_t k = 0; k < totalMine; ++k) {
				size_t i = indices[k] / width;
				size_t j = indices[k] % width;
				setMine(i, j);
			}

		}

		void generate(size_t mine) {
			setTotalMine(mine);
			reset();
		}

		Result onClick(size_t i, size_t j) {
			if (data[i][j].state != TileState::HIDDEN) return Result::NONE;
			if (data[i][j].isMine) return Result::LOSE;
			--hidden;
			data[i][j].state = TileState::REVEALED;
			if (hidden == 0) return Result::WIN;
			if (data[i][j].nearbyMines == 0) {
				for (int ni = -1; ni <= 1; ni++) {
					for (int nj = -1; nj <= 1; nj++) {
						if (isValid(i + ni, j + nj))
							onClick(i + ni, j + nj);
					}
				}
			}
			return Result::NONE;
		}

		Result setFlag(size_t i, size_t j) {
			if (data[i][j].state == TileState::REVEALED) return Result::NONE;
			if (data[i][j].state == TileState::HIDDEN) {
				--hidden;
				data[i][j].state = TileState::FLAGGED;
			}
			else {
				++hidden;
				data[i][j].state = TileState::HIDDEN;
			}
			if (hidden == 0) return Result::WIN;
			return Result::NONE;
		}

		void allOpen() {
			for (auto &i : data) {
				for (auto &j : i) {
					if (j.state == TileState::HIDDEN)
						j.state = TileState::REVEALED;
				}
			}
		}

		void render(Natsuki::Renderer &ren, int size, SDL_Point start = {0, 0}) {
			for (size_t i{}; i < height; ++i) {
				for (size_t j{}; j < width; ++j) {
					SDL_FRect src{0, 0, 16, 16};
					SDL_FRect dst{i * size, j * size, size, size};
					if (data[i][j].state == TileState::HIDDEN) {
						src.x = 16;
						src.y = 32;
					}
					else if (data[i][j].state == TileState::FLAGGED) {
						src.x = 48;
						src.y = 32;
					}
					else {
						if (data[i][j].isMine) {
							src.x = 32;
							src.y = 32;
						}
						else {
							if (data[i][j].nearbyMines == 0) {
								src.y = 32;
							}
							else if (data[i][j].nearbyMines < 5) {
								src.x = (data[i][j].nearbyMines - 1) * 16;
							}
							else {
								src.y = 16;
								src.x = (data[i][j].nearbyMines - 5) * 16;
							}
						}
					}
					ren.render(texture, src, dst);
				}
			}
		}
	};
}