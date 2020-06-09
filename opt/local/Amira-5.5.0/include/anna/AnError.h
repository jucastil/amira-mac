/*****************************************************************************
 *
 * anna -- expression parsing library 
 *
 * Copyright 1993-1997 by Malte Zoeckler and Johannes Schmidt-Ehrenberg
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE ;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of the copyright holders
 *
 ****************************************************************************/
// AnError.h
#ifndef __ERROR_H_
#define __ERROR_H_

#include "AnnaWinDLLApi.h"

#ifndef _WIN32
#include <float.h>
#define MAXVAL DBL_MAX
#define MINVAL (-1*DBL_MAX)
#else
#define MAXVAL  1.7E308
#define MINVAL  -1.7E308
#endif
#define LN_MAXVAL 709.72

#define VAR_UNKNOWN                     1
#define UNKNOWN_VAR_INSTANCE_REQUEST    2
#define SYNTAX                          3
#define UNKNOWN_VAR_KILL_REQUEST        4
#define DIFF_IMPOSSIBLE                 5
#define NUMBER_OF_ARGUMENTS_CHANGED     6
#define ILLEGAL_OPTION                  7
#define DIVISION_BY_ZERO                8
#define OVFLOW                          9
#define UNDRFLOW                        10
#define ILLEGAL_LOG_ARGUMENT            11
#define RADIKAND_NEGATIV                12
#define ZWEI_OPERATOREN                 13
#define ARCUS_RANGE                     14
#define MV_NULL_INSERTED                100
#define MV_LOW_MEMORY                   101
#define MV_NO_MEMORY                    102
#define ILLEGAL_ARGUMENT                666 //RK

ANNA_API const char * vAnError(int);
extern int ANNA_API AnError;

#endif

