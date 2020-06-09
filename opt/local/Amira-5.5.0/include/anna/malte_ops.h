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
#include "Anna.h"
#include <mclibthreaded/McMutex.h>

/// 
class AnGauss : public Anna
{
public:
  	AnGauss();
    int identify();
    const char* symbol();

	double value(double *varValues, int &anError) const;

    //Anna* diff(const char* var);
    Anna* dup();

protected:
    static McMutex m_mutex;
};

///
class AnRand : public Anna
{
public:
	AnRand();

    int identify();
    const char* symbol();

	double value(double *varValues, int &anError) const;

    Anna* diff(const char* var);
    Anna* dup();

    ///Returns the number of bytes needed for the buffer given to print().
	int count();

    ///Prints the expression to the given character array (see count()).
    int print(char* text);

    ///value-constant
	int vconstant() {return 0;}

    ///parameter-constant for diff(AnVarnode *)
    int pconstant(const char*) {return 1;}
};
