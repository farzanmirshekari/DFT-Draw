#pragma once

#define FRAME_RATE 144
#define MAX_FREQUENCY 300
#define MIN_FREQUENCY -300
#define WIDTH 2600
#define HEIGHT 1800
#define STORAGE_THRESHOLD 22.5 * FRAME_RATE
#define dt 0.025 * (MAX_FREQUENCY - MIN_FREQUENCY) / MAX_FREQUENCY / FRAME_RATE 