/*********************************************************************
*                SEGGER MICROCONTROLLER GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2003-2007     SEGGER Microcontroller GmbH & Co KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emFile file system for embedded applications ****
emFile is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : FS_ConfigRAMDisk_23k.c
Purpose     : Configuration file for FS with RAM disk
---------------------------END-OF-HEADER------------------------------
*/

#include "FS.h"

/*********************************************************************
*
*       Defines, configurable
*
*       This section is the only section which requires changes
*       using the RAM disk driver as a single device.
*
**********************************************************************
*/
#define ALLOC_SIZE          0x1100    // Memory pool for the file system in bytes
#define NUM_SECTORS         46        // Number of sectors on the RAM storage
#define BYTES_PER_SECTOR    512       // Size of a sector in bytes

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

//
// Memory pool used for semi-dynamic allocation and memory for storage.
//
#ifdef __ICCARM__
  #pragma location="FS_RAM"
  static __no_init U32 _aMemBlock[ALLOC_SIZE / 4];
  #pragma location="FS_RAM"
  static __no_init U32 _aRAMDisk[(NUM_SECTORS * BYTES_PER_SECTOR) / 4];
#elif defined __CC_ARM
  __attribute__ ((section ("FS_RAM"), zero_init))
  U32 static _aMemBlock[ALLOC_SIZE / 4];
  __attribute__ ((section ("FS_RAM"), zero_init))
  U32 static _aRAMDisk[(NUM_SECTORS * BYTES_PER_SECTOR) / 4] ;
#elif (defined __SES_ARM) || defined (__GNUC__)
  __attribute__ ((section ("FS_RAM")))
  static U32 _aMemBlock[ALLOC_SIZE / 4];
  __attribute__ ((section ("FS_RAM")))
  static U32 _aRAMDisk[(NUM_SECTORS * BYTES_PER_SECTOR) / 4] ;
#else
  static U32 _aMemBlock[ALLOC_SIZE / 4];
  static U32 _aRAMDisk[(NUM_SECTORS * BYTES_PER_SECTOR) / 4];
#endif

/*********************************************************************
*
*       Public code
*
*       This section does not require modifications in most systems.
*
**********************************************************************
*/

/*********************************************************************
*
*       FS_X_AddDevices
*
*  Function description
*    This function is called by the FS during FS_Init().
*    It is supposed to add all devices, using primarily FS_AddDevice().
*
*  Note
*    (1) Other API functions may NOT be called, since this function is called
*        during initialization. The devices are not yet ready at this point.
*/
void FS_X_AddDevices(void) {
  FS_AssignMemory(&_aMemBlock[0], sizeof(_aMemBlock));
  //
  // Add and configure the driver.
  //
  FS_AddDevice(&FS_RAMDISK_Driver);
  FS_RAMDISK_Configure(0, _aRAMDisk, BYTES_PER_SECTOR, NUM_SECTORS);
#if FS_SUPPORT_FILE_BUFFER
  //
  // Enable the file buffer to increase the performance when reading/writing a small number of bytes.
  //
  FS_ConfigFileBufferDefault(BYTES_PER_SECTOR, FS_FILE_BUFFER_WRITE);
#endif
}

/*********************************************************************
*
*       FS_X_GetTimeDate
*
*  Description:
*    Current time and date in a format suitable for the file system.
*
*    Bit 0-4:   2-second count (0-29)
*    Bit 5-10:  Minutes (0-59)
*    Bit 11-15: Hours (0-23)
*    Bit 16-20: Day of month (1-31)
*    Bit 21-24: Month of year (1-12)
*    Bit 25-31: Count of years from 1980 (0-127)
*/
U32 FS_X_GetTimeDate(void) {
  U32 r;
  U16 Sec, Min, Hour;
  U16 Day, Month, Year;

  Sec   = 0;        // 0 based.  Valid range: 0..59
  Min   = 0;        // 0 based.  Valid range: 0..59
  Hour  = 0;        // 0 based.  Valid range: 0..23
  Day   = 1;        // 1 based.    Means that 1 is 1. Valid range is 1..31 (depending on month)
  Month = 1;        // 1 based.    Means that January is 1. Valid range is 1..12.
  Year  = 0;        // 1980 based. Means that 2007 would be 27.
  r   = Sec / 2 + (Min << 5) + (Hour  << 11);
  r  |= (U32)(Day + (Month << 5) + (Year  << 9)) << 16;
  return r;
}

/*************************** End of file ****************************/
