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
#ifndef CONVERTER_H
#define CONVERTER_H

#include "AnnaWinDLLApi.h"
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McHashTable.h>

class Anna;
class AnDepVarnode;

///
class ANNA_API AnConverter
{
protected:
public:
  ///
  static Anna *strToAnna(const char*, McDArray<McString> &v, int numdepvars=0, AnDepVarnode *dv[]=0);

  static Anna* strToAnna(const char*, McDArray<McString> &v, McHashTable<McString,McString>* varAlias, int numdepvars=0, AnDepVarnode *dv[]=0);
};
#endif

