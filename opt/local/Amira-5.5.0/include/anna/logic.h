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

// Deklaration der Klassen AnLess, AnEqual, AnGreater, AnUnequal, AnLessequal, greaterequal, AnOr, AnAnd, AnNot 

#ifndef __LOGIC_H
#define __LOGIC_H 

#include "AnBinary.h"
#include "AnUnary.h"

///
class AnLess : public AnBinary
{
  public:
	AnLess(Anna *a,Anna *n):AnBinary(a,n){;};
///
      //  virtual int priority();
///
//	int  identify(void);
///
//	virtual char *symbol();
    double value(double *varValues, int &anError) const
    {
        int err1=0, err2=0;
        double res = (arg->value(varValues, err1) < next->value(varValues,err2) );
        if (err1>0)
            anError = err1;
        else if (err2>0)
            anError = err2;

        return res;
    };
///
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnLess(arg->dup(), next->dup())); }
};

///
class AnGreater : public AnBinary
{
  public:
	AnGreater(Anna *a,Anna *n):AnBinary(a,n){;};
///
//    virtual int priority();
///
//	int  identify(void);
///
//	virtual char *symbol();
    double value(double *varValues, int &anError) const
    {
        int err1=0, err2=0;
        double res = (arg->value(varValues, err1) > next->value(varValues,err2) );
        if (err1>0)
            anError = err1;
        else if (err2>0)
            anError = err2;

        return res;
    };
///
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnGreater(arg->dup(), next->dup())); }
};


///
class AnEqual : public AnBinary
{
  public:
///
	AnEqual(Anna *a,Anna *n):AnBinary(a,n){;}
///
//    virtual int priority();
///
//	int  identify(void);
///
//	virtual char *symbol();
///
    double value(double *varValues, int &anError) const;
///
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnEqual(arg->dup(), next->dup())); }
};


///
class AnLessEqual : public AnBinary
{
  public:
///
	AnLessEqual(Anna *a,Anna *n) : AnBinary(a,n) { }
///
	//    virtual int priority();
///
    //	int  identify(void);
///
    //	virtual char *symbol();
///
    double value(double *varValues, int &anError) const
    {
        int err1=0, err2=0;
        double res = (arg->value(varValues, err1) <= next->value(varValues,err2) );
        if (err1>0)
            anError = err1;
        else if (err2>0)
            anError = err2;

        return res;
    };
///
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnLessEqual(arg->dup(), next->dup())); }
};

///
class AnGreaterEqual : public AnBinary
{
  public:
///
	AnGreaterEqual(Anna *a,Anna *n) : AnBinary(a,n){ }
///
	  //    virtual int priority();
///
	  //	int  identify(void);
///
	  //	virtual char *symbol();
///
    double value(double *varValues, int &anError) const
    {
        int err1=0, err2=0;
        double res = (arg->value(varValues, err1) >= next->value(varValues,err2) );
        if (err1>0)
            anError = err1;
        else if (err2>0)
            anError = err2;

        return res;
    };
///
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnGreaterEqual(arg->dup(), next->dup())); }
};

///
class AnOr : public AnBinary
{
  public:
///
	AnOr(Anna *a,Anna *n):AnBinary(a,n){;}
// @ManMemo:
 //   virtual int priority();
// @ManMemo:
//	int  identify(void);
// @ManMemo:
//	virtual char *symbol();
///
    double value(double *varValues, int &anError) const;
// @ManMemo:
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnOr(arg->dup(), next->dup())); }
};

///
class AnAnd : public AnBinary
{
  public:
///
	AnAnd(Anna *a,Anna *n):AnBinary(a,n){;}
///
//    virtual int priority();
///
//	int  identify(void);
///
//	virtual char *symbol();
///
    double value(double *varValues, int &anError) const;
///
//	Anna *diff\(const char **);

	Anna* dup() { return(new AnAnd(arg->dup(), next->dup())); }
};

///
class AnNot : public AnUnary
{
  public:
///
  AnNot(Anna *a):AnUnary(a){;}
// @ManMemo:
//	int priority();
// @ManMemo:
//	Anna *diff\(const char **);
///
    double value(double *varValues, int &anError) const;
// @ManMemo:
//	int  identify(void);
// @ManMemo:
//	char *symbol();
  protected:

	Anna* dup() { return (new AnNot(arg->dup())); }
};

#endif
