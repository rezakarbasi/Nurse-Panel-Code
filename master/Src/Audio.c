#include "Audio.h"

AUDIO_FILE_HANDLER audio_file;
char SD_buff[Date_Per_100ms];

/**
  * @brief  Initialize the wave header file
  * @param  pHeadBuf:Pointer to a buffer
	*	@param	NumSamples:number of samples ( not every time equal to number of bites )
	*	@param	audio:data that to be stored
  * @retval None
  */
uint8_t WavaRecorderHeaderInit(uint8_t* pHeadBuf,int NumSamples)//,uint8_t* audio)
{
	uint32_t ByteRate=SampleRate * NumChannels * BitsPerSample/8;
	uint32_t BlockAlign=NumChannels * BitsPerSample/8;
	uint32_t Subchunk2Size=NumSamples * NumChannels * BitsPerSample/8;
	uint32_t ChunkSize=36 + Subchunk2Size;
	
  /* ChunkID	:	Contains the letters "RIFF" in ASCII form
                (0x52494646 big-endian form)	*/
  pHeadBuf[0] = 'R';
  pHeadBuf[1] = 'I';
  pHeadBuf[2] = 'F';
  pHeadBuf[3] = 'F';

  /* ChunkSize	:	36 + SubChunk2Size, or more precisely:
                  4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                  This is the size of the rest of the chunk 
                  following this number.  This is the size of the 
                  entire file in bytes minus 8 bytes for the
                  two fields not included in this count:
                  ChunkID and ChunkSize.	*/
  pHeadBuf[4]  = (uint8_t)((ChunkSize & 0xFF));
  pHeadBuf[5]  = (uint8_t)((ChunkSize >> 8) & 0xFF);
  pHeadBuf[6]  = (uint8_t)((ChunkSize >> 16) & 0xFF);
  pHeadBuf[7]  = (uint8_t)((ChunkSize >> 24) & 0xFF);

  
  /* Format			:	Contains the letters "WAVE" */
  pHeadBuf[8]  = 'W';
  pHeadBuf[9]  = 'A';
  pHeadBuf[10] = 'V';
  pHeadBuf[11] = 'E';

	/* Subchunk1ID	:	Contains the letters "fmt " */
  pHeadBuf[12]  = 'f';
  pHeadBuf[13]  = 'm';
  pHeadBuf[14]  = 't';
  pHeadBuf[15]  = ' ';

	/* Subchunk1Size	:	16 for PCM.  This is the size of the
                      rest of the Subchunk which follows this number.*/
  pHeadBuf[16]  = 0x10;
  pHeadBuf[17]  = 0x00;
  pHeadBuf[18]  = 0x00;
  pHeadBuf[19]  = 0x00;

	/* AudioFormat		:	PCM = 1 (i.e. Linear quantization)
											Values other than 1 indicate some 
                      form of compression.*/
  pHeadBuf[20]  = 0x01;
  pHeadBuf[21]  = 0x00;

	/* NumChannels		: Mono = 1, Stereo = 2, etc.*/
  pHeadBuf[22]  = 0x01;
  pHeadBuf[23]  = 0x00;

	/* SampleRate	: 8000, 44100, etc.*/
  pHeadBuf[24]  = (uint8_t)((SampleRate & 0xFF));
  pHeadBuf[25]  = (uint8_t)((SampleRate >> 8) & 0xFF);
  pHeadBuf[26]  = (uint8_t)((SampleRate >> 16) & 0xFF);
  pHeadBuf[27]  = (uint8_t)((SampleRate >> 24) & 0xFF);

	/* ByteRate	: == SampleRate * NumChannels * BitsPerSample/8*/
  pHeadBuf[28]  = (uint8_t)((ByteRate & 0xFF));
  pHeadBuf[29]  = (uint8_t)((ByteRate >> 8) & 0xFF);
  pHeadBuf[30]  = (uint8_t)((ByteRate >> 16) & 0xFF);
  pHeadBuf[31]  = (uint8_t)((ByteRate >> 24) & 0xFF);

	/* BlockAlign	:	== NumChannels * BitsPerSample/8
                  The number of bytes for one sample including
                  all channels. I wonder what happens when
                  this number isn't an integer?*/
  pHeadBuf[32]  = (uint8_t)((BlockAlign & 0xFF));
  pHeadBuf[33]  = (uint8_t)((BlockAlign >> 8) & 0xFF);

	/*BitsPerSample	: 8 bits = 8, 16 bits = 16, etc.*/
  pHeadBuf[34]  = (uint8_t)((BitsPerSample & 0xFF));
  pHeadBuf[35]  = (uint8_t)((BitsPerSample >> 8) & 0xFF);
	
	/* ExtraParamSize	: if PCM, then doesn't exist
     X   ExtraParams      space for extra parameters*/
						
	/*Subchunk2ID	:	Contains the letters "data"*/
  pHeadBuf[36]  = 'd';
  pHeadBuf[37]  = 'a';
  pHeadBuf[38]  = 't';
  pHeadBuf[39]  = 'a';
	
	/*	Subchunk2Size	:	== NumSamples * NumChannels * BitsPerSample/8
                      This is the number of bytes in the data.
                      You can also think of this as the size
                      of the read of the subchunk following this 
                      number.*/
  pHeadBuf[40]  = (uint8_t)((Subchunk2Size & 0xFF));
  pHeadBuf[41]  = (uint8_t)((Subchunk2Size >> 8) & 0xFF);
  pHeadBuf[42]  = (uint8_t)((Subchunk2Size >> 16) & 0xFF);
  pHeadBuf[43]  = (uint8_t)((Subchunk2Size >> 24) & 0xFF);

//	/*Data	: The actual sound data.*/
//  for (int count = 0; count < NumSamples*BitsPerSample/8 ; count ++)
//  {
//    pHeadBuf[count+44] = audio[count];
//  }
//  
//  /* Return 0 if all operations are OK */
  return 0;
}

FRESULT Start_Recording(uint16_t min,uint16_t hour, uint16_t day,uint16_t month){
	uint8_t bb;
	
	audio_file.counter=0;
	audio_file.buffer_counter=0;
	
	sprintf(audio_file.path,"%02d%02d%02d%02d.wav",month%100,day%100,hour%100,min%100);

	audio_file.fres=0;

	disk_initialize(0);
	f_mount(&audio_file.fs,"", 1);
	audio_file.fres|= f_open(&audio_file.fil,audio_file.path,FA_CREATE_NEW);
	f_close(&audio_file.fil);
	
	if(audio_file.fres==0){
		disk_initialize(0);
		f_mount(&audio_file.fs,"",1);
		audio_file.fres|=f_open(&audio_file.fil,audio_file.path,FA_WRITE | FA_OPEN_ALWAYS);
		WavaRecorderHeaderInit((uint8_t *)SD_buff,10);
		/*audio_file.fres|=*/audio_file.fres|=f_write(&audio_file.fil,(uint8_t *)SD_buff,44,(unsigned int *)&bb);
	}
	
	return audio_file.fres;
}
