#define AS5600_ADDRESS      0x36
#define ZMCO		        0x00
#define ZPOS_H		        0x01
#define ZPOS_L		        0x02
#define MPOS_H		        0x03
#define MPOS_L		        0x04
#define MANG_H		        0x05
#define MANG_L		        0x06
#define CONF_L		        0x07
#define CONF_H		        0x08
#define	RAWANG_H	        0x0C
#define RAWANG_L	        0x0D
#define ANGLE_H		        0x0E
#define ANGLE_L		        0x0F
#define STATUS		        0x0B
#define AGC			        0x1A
#define MAGN_H		        0x1B
#define MAGN_L		        0x1C
#define BURN		        0xFF
#define	CONF_L_PM           0x03		
#define CONF_H_SF           0x03		
#define CONF_H_FTH          0x1C		
#define CONF_H_WD           0x20
#define	MAGNET_LOW  	    0x10
#define MAGNET_HIGH	        0x20
#define MAGNET_NORM         0x30
#define HYST_MASK		    0x0C
#define HYST_OFF		    0x00
#define HYST_1LSB		    0x04
#define HYST_2LSB		    0x08
#define HYST_3LSB		    0x0C
#define	OUT_STG_MASK    	0x30
#define	OUT_STG_ANALOG		0x00
#define OUT_STG_ANALOG_RED	0x10
#define	OUT_STG_PWM			0x20
#define PWMF_MASK			0xC0
#define PWMF_115HZ			0x00
#define	PWMF_230HZ			0x40
#define	PWMF_460HZ			0x80
#define PWMF_920HZ			0xC0


class MagneticEncoder {

    public:
        static void WriteRegister(uint8_t reg, uint8_t data);
        static uint8_t ReadRegister(uint8_t reg);
        static uint32_t GetAngle(void);
        static uint16_t GetRawAngle(void);
        static uint8_t GetStatus(void);
        static void SetHystheresis(uint8_t hyst);
        static void SetOutputStage(uint8_t out_stage);
        static void SetPWMFrequency(uint8_t frequency);
};