/*
 * debug.h
 *
 * (C) Copyright 1998
 * Surgical Robotics Lab
 * Charite - Campus Virchow
 * Berlin, Germany
 * All rights reserved.
 * 
 */

#ifndef DEBUG_H
#define DEBUG_H

#ifdef PRINTF_DEBUG

#include <stdio.h>

#define dicomTrace(x) {fprintf(stderr, "Trace: %s[%d] %s\n",__FILE__,__LINE__,x);}
#define dicomDebug(x) {printf x;}

#else

#define dicomTrace(x)
#define dicomDebug(x)

#endif /* PRINTF_DEBUG */

#endif /* DEBUG_H */
