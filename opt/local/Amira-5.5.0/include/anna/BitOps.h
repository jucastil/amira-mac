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
#ifndef _ANNA_BIT_OPS_
#define _ANNA_BIT_OPS_

#include "AnBinary.h"

///
class AnBitOr : public AnBinary
{
public:
    ///
    AnBitOr(Anna *a,Anna *n);
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
};

///
class AnBitAnd : public AnBinary
{
public:
    ///
    AnBitAnd(Anna *a,Anna *n);
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
};

///
class AnBitXOr : public AnBinary
{
public:
    ///
    AnBitXOr(Anna *a,Anna *n);
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
};

///
class AnShiftLeft : public AnBinary
{
public:
    ///
    AnShiftLeft(Anna *a,Anna *n);
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
};

///
class AnShiftRight : public AnBinary
{
public:
    ///
    AnShiftRight(Anna *a,Anna *n);
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
};

#endif
