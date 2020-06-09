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
#ifndef __DEPVAR_H
#define __DEPVAR_H
#include "Anna.h"
#include "AnDepVarnode.h"
/** class that represents dependant variables in Anna-expressions
    
    holds a reference to a AnDepVarnode that is used to evaluate externally defined functions
*/
class ANNA_API AnDepVar : public Anna
{
      private:
///
        AnDepVarnode *depVarnode;
        int component;
        int nArgs;
        Anna** args;
        int nPartials;
        int *partials;

      public:
/** constructor of dependant variables in Anna-expressions
    taking an 
    @c AnDepVarnode - the dependant variable that should be evaluated
    @c aComponent - the component that should be evaluated
    @c anPartials - the derivative level: 0 for primary, 1 for derivative, 2 for Hessian, ...
    @c apartials - int array of partials containing i for derivative with respect to i-th variable

*/
        AnDepVar (AnDepVarnode * aDepVarnode, int aComponent, 
            int anPartials, int* apartials, Anna** aargs);
        ~AnDepVar ();
    ///
    int identify(void);
    ///
    const char *symbol();
    ///
    int count();
    ///
    int print(char *text);
    ///
    double value(double *varValues, int &anError) const;
    ///
    Anna *diff(const char *);
    ///
    Anna *dup(void);
    ///
    int  operator ==(Anna& h);

    int getNumChildren();
    Anna *getChild(int nr);
    void setChild(int nr,Anna *child);

protected:
    /** Implements Simplification. */
    Anna* doSimplify();
};

///
class localdepvar : public AnDepVar
{
private:
    ///
    int argnr;
public:
    ///
    localdepvar (int nr, AnDepVarnode *);
    ///
    //	int identify(void);
    ///
	int getNr();
};
#endif
