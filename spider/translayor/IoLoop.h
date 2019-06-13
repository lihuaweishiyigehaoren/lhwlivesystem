#pragma once

#include <cstdint>

const int32_t MAX_EVENT_COUNT = 5000;
const int32_t MAX_RECV_BUFF = 65535;

#include "EPollLoop.h"
#define IoLoop EPollLoop