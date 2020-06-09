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
#ifndef __SPECIALOPS_H
#define __SPECIALOPS_H 
#include "AnBinary.h"
#include "AnUnary.h"

///Modulo operation
class AnModulo : public AnBinary
{
public:
    ///
    AnModulo(Anna *a,Anna *n);

    virtual int priority();
    ///
    int  identify(void);
    ///
    virtual const char *symbol();
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *AnVar);
    ///
    Anna *dup(void);
};

///
class AnHoch :  public AnBinary
{
public:
    ///
    AnHoch(Anna *a,Anna *n);
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
class AnSinus : public AnUnary
{
public:
    ///
    AnSinus(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnCosinus : public AnUnary
{
public:
    ///
    AnCosinus(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnTangens : public AnUnary
{
public:
    ///
    AnTangens(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnExp : public AnUnary
{
public:
    ///
    AnExp(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnSqroot : public AnUnary
{
public:
    ///
    AnSqroot(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnLn : public AnUnary
{
public:
    ///
    AnLn(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnArcsin : public AnUnary
{
public:
    ///
    AnArcsin(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};
///
class AnArccos : public AnUnary
{
public:
    ///
    AnArccos(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnArctan: public AnUnary
{
public:
    ///
    AnArctan(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnErf: public AnUnary
{
public:
    ///
    AnErf(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};
///
class AnErfc: public AnUnary
{
public:
    ///
    AnErfc(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};

///
class AnBetrag: public AnUnary
{
public:
    ///
    AnBetrag(Anna *a);
    ///
    int priority();
    ///
    Anna *diff(const char *);
    ///
    double value(double *varValues, int &anError) const;
    ///
    int  identify(void);
    ///
    Anna *simple(void);
    ///
    const char *symbol();
protected:
    ///
    Anna *dup(void);
};


#endif
