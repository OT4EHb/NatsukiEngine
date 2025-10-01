#pragma once

#ifdef NATSUKI_EXPORTS
#define NATSUKI __declspec(dllexport)
#else
#define NATSUKI __declspec(dllimport)
#endif