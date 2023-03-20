#pragma once
#include "stm32f1xx_hal.h"

class MotorControl {

    public:
        static void move_to_goal(void);
        static void set_mode(GPIO_PinState m0, GPIO_PinState m1, GPIO_PinState m2);
};