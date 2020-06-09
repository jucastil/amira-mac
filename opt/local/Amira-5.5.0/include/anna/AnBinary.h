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
// Headerfile - Operatorenklassen fuer den Termumformer

// Deklaration der Klasse AnBinary

#ifndef __BINARY_H
#define __BINARY_H 

#ifndef __ANNA_H
#include "Anna.h"
#endif


///
class AnBinary : public Anna
{
protected:
    ///
    Anna *arg,*next;
public:
    ///
    AnBinary(Anna *argument,Anna *naechster);
    ///
    ~AnBinary();
    ///
    virtual int getNumChildren();
    ///
    virtual Anna *getChild(int nr);
    ///
    virtual void setChild(int nr,Anna *child);
};
#endif
