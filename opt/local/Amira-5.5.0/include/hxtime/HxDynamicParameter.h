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

/// @addtogroup hxtime hxtime
/// @{
#ifndef	__HxDynamicParameter_H
#define	__HxDynamicParameter_H

#include <anna/AnnaExpression.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxObject.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortText.h>
#include <hxtime/HxPortTime.h>

class HXTIME_API HxDynamicParameter : public HxModule
{
    HX_HEADER(HxDynamicParameter);

  public:
    /// Constructor.
    HxDynamicParameter();

    void compute();

    /// Specifies the time scale for the animation
    HxPortTime portTime;

    /// Specifies the port for the animation
    HxPortMultiMenu portPort;

    /// Infoport to point the user to the usage of "t" and "u"
    HxPortInfo portUsage;

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /**
     *  Set the formula of a given value port. Return false if the port id doesn't exist.
     */
    virtual bool setValuesPortFormula(const McString& formula, int valuePortId);

    /**
     *  Give the possibility to control invisible ports. If set to true, hidden ports in the module
     *  connected to portData will appeared in the @c portPort list. False by default.
     */
    inline void controlInvisiblePorts(bool controlThem) {m_canControlInvisiblePorts = controlThem;}

    /**
     *  Do not allow time formula update. False by default. Internal use.
     */
    inline void blockTimeFormulaUpadate (bool blockIt) {m_isBlockingTimeFormulaUpdate = blockIt;}

  protected:
    /// Destructor
    ~HxDynamicParameter();

    /// Auxiliary struct to store the ports supported by this module
    struct SupportedPort {
        HxPort* port;
        int nElements;
    };

    McDArray<double> mVarVals;

    ///
    McDArray<AnnaExpression> mAnnaExpr;

    ///
    McDArray<bool> mExpressionIsValid;

    ///
    McDArray<SupportedPort> supportedPorts;

    ///
    McDArray<HxPortText*> valuePorts;

    ///
    int prevViewerMask;

    /// Tell if invisible ports may be controlled by the @c portTime (false by default).
    bool m_canControlInvisiblePorts;

    /// Tell if the time formula update is blocked.
    bool m_isBlockingTimeFormulaUpdate;

    HxObject* prevTimeObject;

    /// Writes a command sequence initializing the ports to fp.
    // We re-implement this method to be sure that the saved time value will be
    // the one which is displayed after re-load.
    virtual void savePorts(FILE* fp);


};
	
#endif


/// @}
