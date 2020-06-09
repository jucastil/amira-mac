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
#ifndef __ZAHL_H
#define __ZAHL_H

#ifndef __ANNA_H
#include "Anna.h"
#endif

///
class ANNA_API AnZahl : public Anna
{
      private:
///
        double wert;
///
	char *symbolbuf;
	public:
///
        AnZahl(double v);
        ~AnZahl();
///
        virtual int  identify(void);
///
    virtual const char *symbol();

        // tree
///
        virtual int count();
///
        virtual int print(char *text);
///
        virtual double value(double *varValues, int &anError) const;
///
        virtual Anna *diff(const char *);
///
        virtual Anna *dup(void);
///
        virtual int  vconstant(void);           // value
///
        virtual int  pconstant(const char *);      // parameter
///
        virtual int  operator ==(Anna& h);
};
#endif

