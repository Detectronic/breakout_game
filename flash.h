
#define USERDATA_FLASH_BASE     (void*)0x0FE00000UL
#define USERDATA_FLASH_SIZE     (void*)0x0FE00400UL

#define CAL_RESULTS_FLASH_BASE  (void*)0x40088000

#define CRC_SIZE                 2

#define CRC_BIT_SHIFT_8          8




void flash_load_user_data();
void flash_save_user_data();



