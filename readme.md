# Natsuki Engine
Это можно назвать ~~игровым движком~~ фреймворком
для разработки игр (не рекомендуется к использованию)

## Зависимости
Используются библиотеки [SDL3](https://github.com/libsdl-org/SDL),
[SDL_image](https://github.com/libsdl-org/SDL_image),
[SDL_ttf](https://github.com/libsdl-org/SDL_ttf),
[SDL_mixer](https://github.com/libsdl-org/SDL_mixer)

## Сборка
Доступна сборка через CMake, протестирована с Ninja + MSVC.

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

## Примеры
Представлены в директории example

## Реализованные системы
В данный момент реализованы абстракции над библиотекой (не рекомендуется к использованию),
менеджер ресурсов (не рекомендуется к использованию),
конечный автомат игровых состояний (не рекомендуется к использованию, будет переписан на компилтайм (уже сломался)),
звуковая система (не рекомендуется к использованию)