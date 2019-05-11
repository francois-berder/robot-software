#pragma once

#ifdef __cplusplus
#include <uavcan/uavcan.hpp>

int electron_starter_init(uavcan::INode& node);
bool electron_is_arrived();

extern "C" {
#endif

/** Tells the electron to move up */
void electron_starter_start(void);

#ifdef __cplusplus
}
#endif
