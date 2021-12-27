// #include <stdio.h>

// #define BROADCAST_ID        0xFE    // 254
// #define MAX_ID              0xFC    // 252

// /* Macro for Control Table Value */
// #define DXL_MAKEWORD(a, b)  ((uint16_t)(((uint8_t)(((uint64_t)(a)) & 0xff)) | ((uint16_t)((uint8_t)(((uint64_t)(b)) & 0xff))) << 8))
// #define DXL_MAKEDWORD(a, b) ((uint32_t)(((uint16_t)(((uint64_t)(a)) & 0xffff)) | ((uint32_t)((uint16_t)(((uint64_t)(b)) & 0xffff))) << 16))
// #define DXL_LOWORD(l)       ((uint16_t)(((uint64_t)(l)) & 0xffff))
// #define DXL_HIWORD(l)       ((uint16_t)((((uint64_t)(l)) >> 16) & 0xffff))
// #define DXL_LOBYTE(w)       ((uint8_t)(((uint64_t)(w)) & 0xff))
// #define DXL_HIBYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 8) & 0xff))

// /* Instruction for DXL Protocol */
// #define INST_PING               1
// #define INST_READ               2
// #define INST_WRITE              3
// #define INST_REG_WRITE          4
// #define INST_ACTION             5
// #define INST_FACTORY_RESET      6
// #define INST_SYNC_WRITE         131     // 0x83
// #define INST_BULK_READ          146     // 0x92
// // --- Only for 2.0 --- //
// #define INST_REBOOT             8
// #define INST_CLEAR              16      // 0x10
// #define INST_STATUS             85      // 0x55
// #define INST_SYNC_READ          130     // 0x82
// #define INST_BULK_WRITE         147     // 0x93

// // Communication Result
// #define COMM_SUCCESS        0       // tx or rx packet communication success
// #define COMM_PORT_BUSY      -1000   // Port is busy (in use)
// #define COMM_TX_FAIL        -1001   // Failed transmit instruction packet
// #define COMM_RX_FAIL        -1002   // Failed get status packet
// #define COMM_TX_ERROR       -2000   // Incorrect instruction packet
// #define COMM_RX_WAITING     -3000   // Now recieving status packet
// #define COMM_RX_TIMEOUT     -3001   // There is no status packet
// #define COMM_RX_CORRUPT     -3002   // Incorrect status packet
// #define COMM_NOT_AVAILABLE  -9000   //

// class PacketHandler
// {
//     private:

//     public:

// };