
#include "SD_functions.h"

char append_string(
		const TCHAR* path,			/* path of the file or file name */
		const TCHAR* fmt,				/* data wanted to store */
		UINT btw								/* Number of bytes to write */
)
{
	
	FRESULT fr;
  FATFS fs;
  FIL fil;

  /* Open or create a log file and ready to append */
  fr=f_mount(&fs, "", 1);	

	fr = open_append(&fil,path);
  //if (fr != FR_OK) return 1;
	
  /* Append a line */
  if(btw==0)
		fr=f_printf(&fil,fmt);
	else	{
		UINT* bw;
		f_write(&fil,fmt,btw,bw);
	}
	/* Close the file */
  f_close(&fil);
}


FRESULT read_file(
	char buff[],
	const TCHAR* path,			/* path of the file or file name */
	int size								/* size want to read */
){
	
	FRESULT fr;
  FATFS fs;
  FIL fil;
	
  /* Open or create a log file and ready to append */
  fr=f_mount(&fs,"", 1);	
	
	f_open(&fil,path,FA_READ);
	
	if(size==0)size=f_size(&fil);
	
	unsigned int size_r=0;
	
	fr=f_read(&fil,buff,size,&size_r);

	/* Close the file */
  f_close(&fil);
	
	return fr;
}


FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
)
{
    FRESULT fr;

    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    return fr;
}

FRESULT make_file(const char* path    /* [IN]  File name to be create */){
	FRESULT fr;
  FATFS fs;
  FIL fil;
	
	fr=f_mount(&fs,"", 1);
	fr = f_open(&fil,path,FA_CREATE_NEW);
	f_close(&fil);
	
	return fr;
}

//void print_state(int s){
//	
//	ILI9341_Draw_Text("                                      ", 20, 50, BLACK, 2, WHITE);
//	
//	switch (s) {
//		case FR_OK:
//			ILI9341_Draw_Text("FR_OK", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_DISK_ERR:
//			ILI9341_Draw_Text("FR_DISK_ERR", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_INT_ERR:
//			ILI9341_Draw_Text("FR_INT_ERR", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_NOT_READY:
//			ILI9341_Draw_Text("FR_NOT_READY", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_NO_FILE:
//			ILI9341_Draw_Text("FR_NO_FILE", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_NO_PATH:
//			ILI9341_Draw_Text("FR_NO_PATH", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_INVALID_NAME:
//			ILI9341_Draw_Text("FR_INVALID_NAME", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_DENIED:
//			ILI9341_Draw_Text("FR_DENIED", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_EXIST:
//			ILI9341_Draw_Text("FR_EXIST", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_INVALID_OBJECT:
//			ILI9341_Draw_Text("FR_INVALID_OBJECT", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_WRITE_PROTECTED:
//			ILI9341_Draw_Text("FR_WRITE_PROTECTED", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_INVALID_DRIVE:
//			ILI9341_Draw_Text("FR_INVALID_DRIVE", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_NOT_ENABLED:
//			ILI9341_Draw_Text("FR_NOT_ENABLED", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_NO_FILESYSTEM:
//			ILI9341_Draw_Text("FR_NO_FILESYSTEM", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_MKFS_ABORTED:
//			ILI9341_Draw_Text("FR_MKFS_ABORTED", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_TIMEOUT:
//			ILI9341_Draw_Text("FR_TIMEOUT", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_LOCKED:
//			ILI9341_Draw_Text("FR_LOCKED", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_NOT_ENOUGH_CORE:
//			ILI9341_Draw_Text("FR_NOT_ENOUGH_CORE", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_TOO_MANY_OPEN_FILES:
//			ILI9341_Draw_Text("FR_TOO_MANY_OPEN_FILES", 25, 50, BLACK, 2, WHITE);
//		break;
//		
//		case FR_INVALID_PARAMETER:
//			ILI9341_Draw_Text("FR_INVALID_PARAMETER", 25, 50, BLACK, 2, WHITE);
//		break;
//	}
//}