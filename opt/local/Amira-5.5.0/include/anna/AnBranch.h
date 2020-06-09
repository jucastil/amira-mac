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
#ifndef __BRANCH_H
#define __BRANCH_H 

#ifndef __ANNA_H
#include "Anna.h"
#endif


///
class AnBranch : public Anna
{
public:
    ///
    AnBranch(Anna* _left = 0, Anna* _right = 0);
    ///
    ~AnBranch();
    ///
    virtual int getNumChildren();
    ///
    virtual Anna* getChild(int nr);
    ///
    virtual void setChild(int nr, Anna* child);
    ///
    virtual int priority();
    ///
    int  identify(void);
    ///
    virtual const char *symbol();
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna* diff(const char *);
    ///
    Anna* dup(void);

    int operator ==(Anna& h);

protected:
	///
    Anna* left;
    Anna* right;
    
    ///
    Anna* doSimplify();
};
#endif

