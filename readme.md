# Natsuki Engine
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://cppreference.com/)
[![SDL3](https://img.shields.io/badge/SDL-3.4.x-green.svg)](https://github.com/libsdl-org/SDL)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/CMake-3.28+-blue.svg)](https://cmake.org/)

**Natsuki Engine** — это модульный 2D-игровой движок на C++20, построенный на современной библиотеке SDL3.

>**Статус проекта:** в разработке.

## Зависимости
Используются библиотеки [SDL3](https://github.com/libsdl-org/SDL),
[SDL_image](https://github.com/libsdl-org/SDL_image),
[SDL_ttf](https://github.com/libsdl-org/SDL_ttf),
[SDL_mixer](https://github.com/libsdl-org/SDL_mixer)

## Быстрый старт
```cmake
#CMakeLists.txt
cmake_minimum_required...
project...
#Configure
add_subdirectory(${ENGINE_ROOT})
add_executable(YourGame)
natsuki_target(YourGame)
natsuki_assets(YourGame ${ASSETS_DIR})
```

## Сборка
Доступна сборка через CMake,
протестирована с Ninja + MSVC, Ninja + GCC:
```bash
cd example/Mineswaper
cmake -B build -G "Ninja"
cmake --build build
```
По умолчанию используются системные библиотеки,
если они не установлены,
возможно собрать их самостоятельно.
Для этого нужно подтянуть их подмодули:
```bash
git submodule update --init --remote
```

## Примеры
Представлены в директории example.
В данный момент только один пример Mineswaper

## Реализованные системы
В данный момент реализованы абстракции над библиотекой,
менеджер ресурсов,
звуковая система
