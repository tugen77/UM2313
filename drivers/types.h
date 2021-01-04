/***********************************************************************
 * Copyright (c)  2017 - 2019, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : type.h
 * Description : type header file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#ifndef __types_h
#define __types_h

typedef   signed           char INT8;
typedef   signed short     int  INT16;
typedef   signed           int  INT32;

/* exact-width unsigned integer types */
typedef unsigned           char UINT8;
typedef unsigned short     int  UINT16;
typedef unsigned           int  UINT32;

typedef unsigned           char BYTE;
typedef unsigned short     int  WORD;
typedef unsigned           int  DWORD;
typedef unsigned           char * PBYTE;
typedef unsigned short     int  * PWORD;
typedef unsigned           int  * PDWORD;

typedef unsigned           char  BOOL;

#define TRUE  1
#define FALSE 0



#endif 




