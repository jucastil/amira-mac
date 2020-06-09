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
#ifndef __BASICBINARY_H
#define __BASICBINARY_H 

#include "AnBinary.h"

///
class AnPlus : public AnBinary
{
public:
    ///
    AnPlus(Anna *a,Anna *n);
    ///
    virtual int priority();
    ///
    int  identify(void);
    ///
    virtual const char *symbol();
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *);
    ///
    Anna *dup(void);

    int operator ==(Anna& h);

protected:
	///
    Anna* doSimplify();
};

///
class AnMinus : public AnBinary
{
public:
    ///
    AnMinus(Anna *a,Anna *n);
    ///
    virtual int priority();
    ///
    int  identify(void);
    ///
    virtual const char *symbol();
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *);
    ///
    Anna *dup(void);

protected:
	///
    Anna* doSimplify();
};

///
class AnMal : public AnBinary
{
public:
    ///
    AnMal(Anna *a,Anna *n);
    ///
    virtual int priority();
    ///
    int  identify(void);
    ///
    virtual const char *symbol();
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *);
    ///
    Anna *dup(void);

    int operator ==(Anna& h);

protected:
	///
    Anna* doSimplify();
};

///
class AnDurch : public AnBinary
{
public:
    ///
    AnDurch(Anna *a,Anna *n);
    ///
    virtual int priority();
    ///
    int  identify(void);
    ///
    virtual const char *symbol();
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *);
    ///
    Anna *dup(void);

protected:
	///
    Anna* doSimplify();
};

#endif
