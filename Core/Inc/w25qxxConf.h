#ifndef _W25QXXCONFIG_H
#define _W25QXXCONFIG_H
#include "sys.h"
#define _W25QXX_SPI hspi1
#define _W25QXX_CS_GPIO FLASH_CS_GPIO_Port
#define _W25QXX_CS_PIN FLASH_CS_Pin
#define _W25QXX_USE_FREERTOS 0
#define _W25QXX_DEBUG 0
#define W25QXX_CS PBout(4)
#define W25QXX_SCK PAout(8)
#define W25QXX_MISO PAin(9)
#define W25QXX_MOSI PAout(10)

#define W25QXX_WP PBout(13)
#define W25QXX_HOLD PBout(14)
#endif
