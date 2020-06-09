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

// Deklaration der Klasse AnUnary

#ifndef __UNARY_H
#define __UNARY_H 

#ifndef __ANNA_H
#include "Anna.h"
#endif

///
class AnUnary : public Anna
{
protected:
    ///
    Anna *arg;
public:
    ///
    AnUnary(Anna *argument);
    ///
    ~AnUnary();
    ///
    virtual int getNumChildren();
    ///
    virtual Anna *getChild(int nr);
    ///
    virtual void setChild(int nr,Anna *child);
    ///
    virtual int print(char *);
    ///
    virtual int count();
};


#endif
