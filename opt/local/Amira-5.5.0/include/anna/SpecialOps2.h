/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup anna anna
/// @{
#ifndef __SPECIALOPS2_H
#define __SPECIALOPS2_H 

#include "AnBinary.h"
#include "AnUnary.h"


////////////////////////////////////////////////////////////////////////////////
class AnArccosh : public AnUnary
{
public:
    ///
    AnArccosh(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnArcsinh : public AnUnary
{
public:
    ///
    AnArcsinh(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnArctan2 : public AnBinary
{
public:
    ///
    AnArctan2( Anna * a, Anna * b );
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


////////////////////////////////////////////////////////////////////////////////
class AnArctanh : public AnUnary
{
public:
    ///
    AnArctanh(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnCbroot : public AnUnary
{
public:
    ///
    AnCbroot(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnCeil : public AnUnary
{
public:
    ///
    AnCeil(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnCopysign : public AnBinary
{
public:
    ///
    AnCopysign( Anna * a, Anna * b );
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


////////////////////////////////////////////////////////////////////////////////
class AnCosh : public AnUnary
{
public:
    ///
    AnCosh(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnDrem : public AnBinary
{
public:
    ///
    AnDrem( Anna * a, Anna * b );
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


////////////////////////////////////////////////////////////////////////////////
class AnExpm1 : public AnUnary
{
public:
    ///
    AnExpm1(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnFloor : public AnUnary
{
public:
    ///
    AnFloor(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnFmod : public AnBinary
{
public:
    ///
    AnFmod( Anna * a, Anna * b );
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

////////////////////////////////////////////////////////////////////////////////

// not yet implemented
#if(0)

class AnGamma : public AnUnary
{
public:
    ///
    AnGamma(Anna *a);
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

////////////////////////////////////////////////////////////////////////////////
class AnHypot : public AnBinary
{
public:
    ///
    AnHypot( Anna * a, Anna * b );
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


////////////////////////////////////////////////////////////////////////////////
class AnJ0 : public AnUnary
{
public:
    ///
    AnJ0(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnJ1 : public AnUnary
{
public:
    ///
    AnJ1(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnJn : public AnBinary
{
public:
    ///
    AnJn( Anna * a, Anna * b );
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


////////////////////////////////////////////////////////////////////////////////
class AnLog10 : public AnUnary
{
public:
    ///
    AnLog10(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnLog1p : public AnUnary
{
public:
    ///
    AnLog1p(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnLogb : public AnUnary
{
public:
    ///
    AnLogb(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnRint : public AnUnary
{
public:
    ///
    AnRint(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnSinh : public AnUnary
{
public:
    ///
    AnSinh(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnTanh : public AnUnary
{
public:
    ///
    AnTanh(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnTrunc : public AnUnary
{
public:
    ///
    AnTrunc(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnY0 : public AnUnary
{
public:
    ///
    AnY0(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnY1 : public AnUnary
{
public:
    ///
    AnY1(Anna *a);
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


////////////////////////////////////////////////////////////////////////////////
class AnYn : public AnBinary
{
public:
    ///
    AnYn( Anna * a, Anna * b );
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


////////////////////////////////////////////////////////////////////////////////
class AnMin : public AnBinary
{
public:
    ///
    AnMin( Anna * a, Anna * b );
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

////////////////////////////////////////////////////////////////////////////////
class AnMax : public AnBinary
{
public:
    ///
    AnMax( Anna * a, Anna * b );
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

////////////////////////////////////////////////////////////////////////////////
class AnSgn : public AnUnary
{
public:
    ///
    AnSgn(Anna *a);
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

/// @}
