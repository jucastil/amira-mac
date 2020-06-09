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
#ifndef __ANNA_H
#define __ANNA_H

#include "AnnaWinDLLApi.h"

#include <mclib/McDArray.h>

/// Encapsulates expression tree.

class ANNA_API Anna 
{
public:
    /// Evaluate the expression.
    virtual double value(double *varValues, int &anError) const = 0;

    /** Returns a new expression, that is the derivation to the variable named var.
	
		This function is \b not assumed to succeed always, i.e., it may return
		a \b NULL pointer. 
        Bear this in mind when implementing diff: the differentiated arguments 
        may be NULL.
	*/
    virtual Anna* diff(const char* var);

    /** Returns a new expression, that is a simplification of the original one.

		This function is assumed to succeed \b always, i.e., it always returns
		a valid pointer.
	*/
    Anna* simplify();

    /** Duplicates expression.

		This function is assumed to succeed \b always, i.e., it always returns
		a valid pointer.
	*/
    virtual Anna* dup() = 0;

    ///
    Anna();
    ///
    virtual ~Anna();    

    ///
    virtual int priority();     
    ///
    virtual int getNumChildren();
    ///
    virtual Anna *getChild(int nr);
    ///
    virtual void setChild(int nr, Anna *child);
    ///
    virtual int identify();
    ///
    virtual const char *symbol();
    
    
    ///Returns the number of bytes needed for the buffer given to print().
    virtual int count();
    ///Prints the expression to the given character array (see count()).
    virtual int print(char* text);

    /** Returns non-zero, if this expression has the same value for all possible variable assignments.

		@note As an example, \f$\cos(0) = 1 = \text{const.}\f$.
	*/
    virtual int vconstant();

    /** Returns non-zero, if this expression is constant with respect to a given variable.
	
		This is called parameter-constancy.
		An expression is called parameter-constant, if changing this one parameter (variable)
		does not change the value() of the expression.
		This is used to ease derivation, see diff().

		@note As an example we look for the parameter-constancy regarding \f$x\f$:
		\f$x=[0,2\pi], y=[0,2\pi]\f$ gives that \f$\cos(y) = \text{pconst(x)}\f$,
		but \f$-1 \leq \cos(x) \leq 1 \neq \text{pconst(x)}\f$.
	*/
    virtual int pconstant(const char *);

    /** Returns non-zero, if expressions are equal.

		Equality is meant in the sense, that they are equal all the time, i.e.,
		for all possible variable assignments they always have the same value().

		@note As an example, \f$a+b = b+a\f$ and \f$a*b = b*a\f$, but \f$a^b \neq b^a\f$
	*/
    virtual int operator ==(Anna& h);

protected:
    /** Implements Simplification. */
    virtual Anna* doSimplify();
};

#endif
