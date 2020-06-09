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

#ifndef ANCHECK_H
#define ANCHECK_H

#include "AnnaWinDLLApi.h"

class Anna;
class AnVarnode;

/** Provides some functions to check the correctness of Anna.
*/
class ANNA_API AnCheck
{
public:
	/** Checks a given symbolic derivation against a numerically obtained 
		one from f. Check is done at numSamples points within the interval
		left...rigth. Returns 0 in case of success.
	*/
	static int checkDerivative(Anna* f, Anna* df, AnVarnode* v,
								double left=0, double right=1, int numSamples=1000);
};

#endif
