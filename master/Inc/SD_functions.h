#ifndef SD_FUNC
#define SD_FUNC

//includes
#include "diskio.h"
#include "ff.h"

#include "stm32f1xx_hal.h"
#include "spi.h"
#include "gpio.h"

//defines
#define disk_init		disk_initialize(0)

//variables

//functions
char append_string(const TCHAR* path,const TCHAR* fmt,UINT btw);
FRESULT open_append(FIL* fp,const char* path);
FRESULT read_file(char buff[],const TCHAR* path,int size);
FRESULT make_file(const char* path);
//void print_state(int s);

#endif
