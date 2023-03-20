#include "motor_control.h"
#include "control_table.h"
#include "utility.h"


void MotorControl::move_to_goal(void) {

    uint32_t goal_position = ControlTable::get(CT::GoalPosition);
    uint32_t present_angle = ControlTable::get(CT::PresentPosition);
    uint32_t tolerance = 2;  // acceptable to be +/- 2 degrees within goal
    uint32_t present_position = (int)(((float)present_angle / 360) * 4095);

    if (present_position < (goal_position - tolerance) || present_position > (goal_position + tolerance)) {

        // determine which direction to go
        if (present_position < goal_position){
            HAL_GPIO_WritePin(STEP_DIR_GPIO_Port, STEP_DIR_Pin, ON);
        } else {
            HAL_GPIO_WritePin(STEP_DIR_GPIO_Port, STEP_DIR_Pin, OFF);
        }
        // take a step
        HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, ON);
        HAL_Delay(1);
        HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, OFF);
        HAL_Delay(1);
    }
}

void MotorControl::set_mode(GPIO_PinState m0, GPIO_PinState m1, GPIO_PinState m2) {
    HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin, m0);
    HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin, m1);
    HAL_GPIO_WritePin(M2_GPIO_Port, M2_Pin, m2);
}