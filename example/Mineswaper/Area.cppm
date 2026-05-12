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
		static constexpr size_t period = 5;
	private:
		std::vector<std::vector<Tile>>data;
		const size_t width;
		const size_t height;
		size_t totalMine;
		std::mt19937 rng;
		std::uniform_int_distribution<size_t> distX;
		std::uniform_int_distribution<size_t> distY;
		Natsuki::Texture texture;
		size_t hidden;
		size_t mines;
		uint16_t count;

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

		void dropMine(size_t i, size_t j) {
			data[i][j].isMine = false;
			for (int di = -1; di <= 1; ++di) {
				for (int dj = -1; dj <= 1; ++dj) {
					if (di == 0 && dj == 0) continue;

					int ni = static_cast<int>(i) + di;
					int nj = static_cast<int>(j) + dj;

					if (isValid(ni, nj)) {
						if (--(data[ni][nj].nearbyMines) == 0
							&& data[ni][nj].state == TileState::REVEALED)
							open(ni, nj);
					}
				}
			}
		}

		void setTotalMine(size_t mine) {
			size_t limit = static_cast<size_t>(width * height * 0.4);
			totalMine = std::min(mine, limit);
			mines = totalMine;
		}

		bool findHidden(size_t &i, size_t &j) {
			for (int k{}; k < 10; ++k) {
				i = distX(rng);
				j = distY(rng);
				if (data[i][j].state == TileState::HIDDEN
					&& data[i][j].isMine == false) return true;
			}
			return false;
		}

		bool findMine(size_t &i, size_t &j) {
			for (int k{}; k < 10; ++k) {
				i = distX(rng);
				j = distY(rng);
				if (data[i][j].isMine == true) return true;
			}
			return false;
		}

		void swapMines() {
			size_t i0, j0;
			if (!findMine(i0, j0)) return;
			size_t i1, j1;
			for (int k{}; k < 10; ++k) {
				if (!findHidden(i1, j1)) return;
				if (i0 != i1 || j0 != j1) {
					setMine(i1, j1);
					dropMine(i0, j0);
					return;
				}
			}
		}

		void open(size_t i, size_t j) {
			--hidden;
			data[i][j].state = TileState::REVEALED;
			if (data[i][j].nearbyMines == 0) {
				for (int di = -1; di <= 1; di++) {
					for (int dj = -1; dj <= 1; dj++) {
						if (di == 0 && dj == 0) continue;
						int ni = i + di;
						int nj = j + dj;
						if (isValid(static_cast<int>(ni), static_cast<int>(nj))
							&& data[ni][nj].state==TileState::HIDDEN) {
							open(ni, nj);
						}
					}
				}
			}
		}
	public:
		Area(size_t width, size_t height, size_t mine, Natsuki::Renderer &ren) :
			width(width), height(height),
			distX(0, width - 1), distY(0, height - 1) {

			Natsuki::checkCall(texture.load("res/minesweeper.png", ren.getRaw()));
			setTotalMine(mine);
			std::random_device rd;
			rng.seed(rd());
			reset();
		}

		void reset() {
			data.assign(height, std::vector<Tile>(width));

			hidden = width * height - mines;
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
			open(i, j);
			if (hidden == 0) return Result::WIN;
			++count;
			if (count % period == 0) {
				count = 0;
				swapMines();
			}
			return Result::NONE;
		}

		void setFlag(size_t i, size_t j) {
			if (data[i][j].state == TileState::REVEALED) return;
			if (data[i][j].state == TileState::HIDDEN) {
				data[i][j].state = TileState::FLAGGED;
			}
			else {
				data[i][j].state = TileState::HIDDEN;
			}
		}

		void allOpen() {
			for (auto &i : data) {
				for (auto &j : i) {
					if (j.state == TileState::HIDDEN)
						j.state = TileState::REVEALED;
				}
			}
		}

		void render(Natsuki::Renderer &ren, float size, Natsuki::Point start = {0, 0}) {
			for (size_t i{}; i < height; ++i) {
				for (size_t j{}; j < width; ++j) {
					Natsuki::FRect src{0.f, 0.f, 16.f, 16.f};
					Natsuki::FRect dst{i * size, j * size, size, size};
					if (data[i][j].state == TileState::HIDDEN) {
						src.x = 16.f;
						src.y = 32.f;
					}
					else if (data[i][j].state == TileState::FLAGGED) {
						src.x = 48.f;
						src.y = 32.f;
					}
					else {
						if (data[i][j].isMine) {
							src.x = 32.f;
							src.y = 32.f;
						}
						else {
							if (data[i][j].nearbyMines == 0) {
								src.y = 32.f;
							}
							else if (data[i][j].nearbyMines < 5) {
								src.x = (data[i][j].nearbyMines - 1) * 16.f;
							}
							else {
								src.y = 16.f;
								src.x = (data[i][j].nearbyMines - 5) * 16.f;
							}
						}
					}
					ren.render(texture, src, dst);
				}
			}
		}
	};
}