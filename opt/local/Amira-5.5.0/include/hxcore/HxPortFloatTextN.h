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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_PORT_FLOAT_TEXT_N
#define HX_PORT_FLOAT_TEXT_N

#include <mclib/McDArray.h>
#include <hxcore/HxPort.h>

class QLabel;
class QLineEdit;
class QSpacerItem;
class HxVirtualSlider;

/** This port represents a variable number of bounded float values which may be
    edited interactively. The actual number of float fields is set in the
    constructor, its default value is 1. In addition to the port's label ( which is set
    by @c HxPort::setLabel) you can define a label for each float field
    using the setLabel() method. You also may set the format string, the
    minimum and maximimum values, as well as the sensitivity of each field.
    If a float field needs not to be shown all of the time you can use
    setPart() to hide or show it. */
class HXCORE_API HxPortFloatTextN : public HxPort {
    MC_ABSTRACT_HEADER(HxPortFloatTextN);

  public:
    /// Actual number of values is defined in constructor.
    HxPortFloatTextN(HxObject *object, const char *name, int n=1);

    /// Actual number of values is defined in constructor.
    HxPortFloatTextN(HxEditor *editor, const char *name, int n=1);

    /// Destructor.
    virtual ~HxPortFloatTextN();

    /// Sets the number of text fields.
    void setNum(int n);

    /// Returns the number of text fields.
    int getNum() const { return parts.size(); }

    /// Sets label of port.
    void setLabel(const char* _label) { HxPort::setLabel(_label); }

    /// Set text of <em> n</em>th label string.
    void setLabel(int n, const char* str);

    /// Returns label of port.
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Get label of specified field.
    const char* getLabel(int n) const;

    /// Show or hide <em> n</em>th float field.
    void setPart(int n, int onOff);

    /// Get value of <em> n</em>th field.
    float getValue(int n=0) const;

    /// Get lower limit of <em> n</em>th field.
    float getMinValue(int n=0) const;

    /// Get upper limit of <em> n</em>th field.
    float getMaxValue(int n=0) const;

    /// Set value of <em> n</em>th field.
    void setValue(int n, float v);

    /// Convenience method to set value of first field.
    void setValue(float v) { setValue(0,v); }

    /// Set limits of <em> n</em>th field.
    void setMinMax(int n, float min, float max);

    /// Convenience method to set limits of all fields.
    void setMinMax(float min, float max);

    /// Set format string for all text fields.
    void setFormat(const char* format);

    /// Set format string for <em> n</em>th field.
    void setFormat(int n, const char* format);

    /// Get format string of specified field.
    const char* getFormat(int n=0) const;

    /// Set sensitivity of field n.
    void setSensitivity(int n, int onOff);

    /// Gt sensitivity of field n.
    int getSensitivity(int n=0) const;

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

    /// fix the step use with virtual slider to a constant value. Use -1 to let the heuristic change the step dynamicaly.
    void setVirtualSliderStep(float value);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );


  protected:
    struct HXCORE_API Part {
        Part();
        ~Part();
        
        void initFrom(const Part* ref );

        float value;
        float min,max;
        McString format;
        McString label;
        unsigned int visible:1;
        unsigned int sensitive:1;
        QxGuardedPtr<QLabel> qLabel;
        QxGuardedPtr<QxLineEdit> qLineEdit;
    };

    McDArray<Part> parts;
    float m_virtualSliderStep;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
    void createWidget(Part* part);

    /**
     * Specific methods to set/retrieve values to/from the GUI.
     */
    virtual float getGUIValue(const Part* part) const;
    virtual void setGUIValue(const Part* part, const float& value);

};

#endif


/// @}
