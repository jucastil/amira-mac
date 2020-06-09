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

/// @addtogroup hxmatlab hxmatlab
/// @{
#ifndef HX_CALCULUS_H
#define HX_CALCULUS_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortTextEdit.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxtime/HxPortTime.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPort3DPointList.h>
#include <hxcore/HxPortDoIt.h>

#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformVectorField3.h>
#include <hxfield/HxUniformComplexScalarField3.h>
#include <hxfield/HxUniformComplexVectorField3.h>
#include <hxfield/HxUniformColorField3.h>

#include <hxmatlab/HxMatlabWinDLLApi.h>
#include <hxmatlab/HxMatlabEng.h>

class HXMATLAB_API HxCalculus:public HxCompModule
{
    HX_HEADER(HxCalculus);

  public:

    HxCalculus();
    ~HxCalculus();

    /// Overloaded to ensure one free port when (dis-)connecting via scripting.
    virtual int parse(Tcl_Interp* t,int argc,char **argv);

    /// Overloaded to ensure one free port when (dis-)connecting via GUI.
    virtual void update();

    /// Overloaded to perform the selected Matlab action.
    virtual void compute();

    /// Reads the given filename from disk and copies the text into the textfield.
    void readFileFromDisk(const char *filename);

    /// Saves the current text in portTextField to the given filename. An error
    /// message will be created if the text cannot be saved.
    void saveFileToDisk(const char *filename);

    HxPortButtonList portReadSave;   ///< Read and save the buffer to file.
    HxPortGeneric    portAction;     ///< Start the processing of the data. See the console for error messages.
    HxPortTextEdit   portTextField;  ///< The Matlab script. You can highlight parts and execute them.
    HxPortToggleList portOptions;    ///< Disable or enable a window displaying the Matlab workspace.
    HxPortDoIt       portApply;      ///< Start the processing of the data. Same as "Execute Buffer".

  protected:

    /// Ensures that there is exactly one free upstream connection port
    /// available. Dynamically adds / removes port to do so.
    void ensureOneFreePort();

    /// Sends data to Matlab.
    bool sendData();

    /// Retrieves data from Matlab.
    bool retrieveData();

    McString   m_lastFilename;  ///< Stores the last used Matlab script filename.
    Engine   * m_eng;           ///< Stores the pointer to the Matlab engine.
};

enum InfoObjectTypes{
    BAD_TYPE,
    STRING_TYPE,
    FLOAT_TYPE
};

class portInfoObject {
public:
    McString name;        // name of the port
    InfoObjectTypes type; // float or strings?
    McDArray<McString> str_values;    // any value(-s) stored as string(-s)
    McDArray<float> float_values;     // any value(-s) stored as float(-s)
    portInfoObject() :
        name(""),
        type(BAD_TYPE),
        str_values(0),
        float_values(0)
    {}
    portInfoObject(McString tname, McString svalue) :
        name(tname),
        str_values(0)
    {
        str_values.append(svalue);
        this->type = STRING_TYPE;
    }
    portInfoObject(McString tname, float fvalue) :
        name(tname),
        float_values(0)
    {
        float_values.append(fvalue);
        this->type = FLOAT_TYPE;
    }
};


#endif

/// @}
