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
#ifndef __AnDEPVARNODE_H
#define __AnDEPVARNODE_H

#include "AnnaWinDLLApi.h"

class McString;

/** Function type that serves as callback of AnDepVarnodes. Is called to actually evaluate the dependant variables

    @c myData - is set in constructor. Used as working space just by the function. Not touched by AnDepVar or AnDepVarnode
    @c component - component index that should be returned
    @c nPartials - derivative level that should be returned. 0 for primary, 1 for Jacobian, 2 for Hessian
    @c apartials - int array of partials containing i for derivative with respect to i-th variable
    @c pos - position where the dependant variable should be evaluated

    See HxAnalyticField in visualFlow/hxfieldxtools for an implementation using dependant variables.
*/
typedef  double (*AnCallbackFunc) (const void* myData, int component, int nPartials, const int* partials, const double* pos);
#define MAX_NDIMS_DEPVAR 10

/** AnDepVarnode is the analogue to AnVarnode for dependant variables.
    
    It represents the dependant variables that can be used in AnDepVar
    in Anna*-expressions.
    AnDepVarnode is therefore refcounted just as AnVarnode.

    Dependant variables can be thought of as functions. 
*/
class ANNA_API AnDepVarnode
{
private:
    ///
    char    * name;
    ///
    int nDims;
    ///
    int nDataVar;
    ///
    int nDiffLevels;
    ///
    McString* defaultVarNames;
    ///
    int* defaultVarIndices;
    ///
    void* myData;
    ///
    AnCallbackFunc AnCallback;
    ///
    int       refCount;


public:

    /// You have to give it a name, nDims, nDataVar, nDiffLevels, AnVarnode-variables it depends on and a void* myData.
                  AnDepVarnode();
    /** Constructor setting name, callback function and the workspace 

        @c text - the name under which this dependant variable can be used in strings that are converted to Anna-expressions
        @c aAnCallback - this function is called when the dependant variable should be evaluated
        @c amyData - void-pointer that serves as workspace for the callback-function

        Before this AnDepVarnode can be used in Anna-expressions, #setUp must be called to set
        the input and output dimensionality and the number of derivatives the AnDepVarnode provides
    */
                  AnDepVarnode(const char *text, AnCallbackFunc aAnCallback, void* amyData);

    ///
                  ~AnDepVarnode();
    /// This is called by AnDepVar to evaluate the function
    double        value(int component, int nPartials, const int* partials, const double* pos);
    void          ref();
    void          unref();
    int           getRefCount() {return refCount;};

    /** setUp has to be called before Anna-expresions containing AnDepVarnodes can be parsed.
        
        @c anDims - the input dimensionality. if < 0, this AnDepVarnode can be set invalid.
        @c anDataVar - the output dimensionality
        @c anDiffLevels - the number of provided levels of differentiation
        @c aDefaultVarNames - names and
        @c aDefaultVarIndices - indices of default parameters, when 
        a AnDepVar is used without parameters. Set to NULL to turn off the 
        possibility of calling without parameters
    */
    void          setUp (int anDims, int anDataVar, int anDiffLevels, char** aDefaultVarNames, int* aDefaultVarIndices);
    void          assertIsValid ();
    bool          isValid () {return nDims >= 0;};

    /// called by the parser to see if it's allowed to call this dependant variables without parameters
    bool          hasDefaultVars ();
    void          setInvalid () {setUp(-1, 0, 0, 0, 0);};
    ///
    const char  * getVar(int i, int &idx);
    ///
    const char  * getName();
    ///     set variables name - use with caution
    void          setName( const char * s ); // RK
    ///
    const int getNDims();
    ///
    const int getNDataVar();
    ///
    const int getNDiffLevels();
    ///
    const void * getMyData();

};

#endif
