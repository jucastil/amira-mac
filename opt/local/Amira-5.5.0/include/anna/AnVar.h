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
#ifndef __VAR_H
#define __VAR_H
#include "Anna.h"

#include <mclib/McString.h>

///
class ANNA_API AnVar : public Anna
{
      private:
///
        int mIndex;

        McString mName;

      public:
///
        AnVar (int idx, const char* name);

        AnVar (int idx, const char* name, Anna* myChild);

        ~AnVar ();
    ///
    int identify(void);
    ///
    const char *symbol();
    ///
    int count();
    ///
    virtual int getNumChildren();
    ///
    virtual Anna* getChild(int nr);
    ///
    virtual void setChild(int nr,Anna *newChild);
    ///
    int print(char* text);
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *);
    ///
    Anna *dup(void);
    ///
    int  vconstant(void);
    ///
    int  pconstant(const char *AnVar);
    ///
    int  operator ==(Anna& h);


protected:
    /** Implements Simplification. */
    Anna* doSimplify();

    Anna* child;
};

///
/*
class localvar : public AnVar
{
private:
    ///
    int argnr;
public:
    ///
    localvar (int nr,AnVarnode *);
    ///
    //	int identify(void);
    ///
	int getNr();
};
*/

#endif
