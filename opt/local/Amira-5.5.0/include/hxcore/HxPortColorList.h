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
#ifndef HX_PORT_COLORLIST
#define HX_PORT_COLORLIST

#include <mclib/McColor.h>
#include <hxcore/HxPort.h>

class HxColorEditor;
class QWidget;
class QLabel;
class QxChooseColorButton;

/** This port defines one or more constant colors.
    The color may be easily changed using the HxColorDialog.
    The Dialog pops up when double-clicking one of the colors.

    See the  @htmlonly <a href= ../usersguide/HxPortColorList.html> usersguide </A> @endhtmlonly 
    for a detailed view of the port's GUI.
*/
class HXCORE_API HxPortColorList : public HxPort {

  MC_ABSTRACT_HEADER(HxPortColorList);

  public:
    /// Constructor for objects.
    HxPortColorList(HxObject *obj, const char *name, int nButtons=1);

    /// Constructor for editors.
    HxPortColorList(HxEditor *editor, const char *name, int nButtons=1);

    /// Destructor.
    virtual ~HxPortColorList();

    /// Returns number of color buttons.
    int getNumButtons() const { return parts.size(); }

    /// Sets the number of color buttons.
    void setNumButtons(int n);

    /// Set color.
    void setColor(const McColor& newColor, int which=0);

    /// Get color.
    void getColor(McColor& color, int which=0);

    /// Get packed color.
    unsigned int getPackedColor(int which=0);
    
    /// Set alpha channel for color number @c which @f$(0 \le newAlpha \le 1)@f$.
    void setAlpha(float newAlpha, int which=0);

    /// Get alpha channel of color number @c which.
    float getAlpha(int which=0);

    /// Returns true if transparency is enabled, i.e. alpha channel < 1.
    int isTransparent(int which=0);

    /// Set label for i'th color field.
    void setLabel(int n, const char* label);

    /// Returns label of specified button.
    const char* getLabel(int n) const;

    /// Seta label of port.
    void setLabel(const char* l) { HxPort::setLabel(l); }

    /// Returns label of port.
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Defines whether object is fired when color is changed interactively.
    void setContinuousMode(bool onOrOff);

    /// Check if continuous mode is enabled.
    int getContinuousMode() const { return continuous; }

    /// Defines whether the alpha channel shall be editable.
    void setAlphaEnabled(bool enabled);

    /// Checks if the alpha channel is editable.
    bool getAlphaEnabled() const;

    /// Tcl parse interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

  protected:
    virtual void createWidget(QWidget* parent);

    struct Part {
        
        void initFrom( const Part* refPart );

        McString             labelString;
        McColor              color;
        float                alpha;
        QxGuardedPtr<QLabel>  label;
        QxGuardedPtr<QxChooseColorButton> button;
    };

    McDArray<Part> parts;
    int continuous;
    bool alphaEnabled;

    virtual void guiCallback();
};

#endif


/// @}
