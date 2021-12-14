#ifndef MESSAGE_TRAFFIC_H
#define MESSAGE_TRAFFIC_H

#include "stm32f1xx_port_handler.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "device.h"

#define DYNAMIXEL_HEADER 0xFFFFFD00

typedef enum {
    UNDEFINED = 0x00,
    PING = 0x01,
    READ = 0x02,
    WRITE = 0x03,
    REG_WRITE = 0x04,
    ACTION = 0x05,
    FACTORY_RESET = 0x06,
    REBOOT = 0x08,
    CLEAR = 0x10,
    CONTROL_TABLE_BACKUP = 0x20,
    STATUS = 0x55,
    SYNC_READ = 0x82,
    SYNC_WRITE = 0x83,
    FAST_SYNC_READ = 0x8A,
    BULK_READ = 0x92,
    BULK_WRITE = 0x93,
    FAST_BULK_READ = 0x9A    
} DInstruction;

typedef enum {
    UNDEFINED_SIZE = 0,
    PING_SIZE = 14,
    READ_SIZE = 0x02,
    WRITE_SIZE = 0x03,
    REG_WRITE_SIZE = 0x04,
    ACTION_SIZE = 0x05,
    FACTORY_RESET_SIZE = 0x06,
    REBOOT_SIZE = 0x08,
    CLEAR_SIZE = 0x10,
    CONTROL_TABLE_BACKUP_SIZE = 0x20,
    STATUS_SIZE = 0x55,
    SYNC_READ_SIZE = 0x82,
    SYNC_WRITE_SIZE = 0x83,
    FAST_SYNC_READ_SIZE = 0x8A,
    BULK_READ_SIZE = 0x92,
    BULK_WRITE_SIZE = 0x93,
    FAST_BULK_READ_SIZE = 0x9A    
} DInstruction_Size;

typedef enum {
    NONE = 0x00,
    RESULT_FAIL = 0x01,
    INSTRUCITON_ERROR = 0x02,
    CRC_ERROR = 0x03,
    DATA_RANGE_ERROR = 0x04,
    DATA_LENGTH_ERROR = 0x05,
    DATA_LIMIT_ERROR = 0x06,
    ACCESS_ERROR = 0x07
} DError;


void processes_received_messages_task(void); 
void transmit_message(uint8_t *, uint8_t);
void respond(uint8_t, int);
int grab_number_of_bytes_L(MessageQueue*, uint8_t);
int grab_number_of_bytes_B(MessageQueue*, uint8_t);
//uint8_t* ping_respond(uint8_t*);
// uint8_t* read_respond(void);
// uint8_t* write_respond(void);
// uint8_t* reg_write_respond(void);
// uint8_t* action_respond(void);
// uint8_t* factory_reset_respond(void);
// uint8_t* reboot_respond(void);
// uint8_t* clear_respond(void);
// uint8_t* control_table_backup_respond(void);
// uint8_t* sync_read_respond(void);
// uint8_t* sync_write_respond(void);
// uint8_t* fast_sync_read_respond(void);
// uint8_t* bulk_read_respond(void);
// uint8_t* bulk_write_repsond(void);
// uint8_t* fast_bulk_read_respond(void);

#endif
