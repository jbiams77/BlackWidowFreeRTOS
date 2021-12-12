#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#ifdef __cplusplus
 extern "C" {
#endif

void start_tasks(void);
void rx_message_task(void *argument);
void tx_message_task(void *argument);
void BLINK_ONBOARD_TASK(void *argument);
void BLINK_OFFBOARD_TASK(void *argument);

#ifdef __cplusplus
}
#endif

#endif
