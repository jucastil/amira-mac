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
#ifndef VIEWERLEGEND_H
#define VIEWERLEGEND_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McHandle.h>
#include <mclib/McString.h>
#include <mclib/McVec3f.h>
#include <mclib/McColor.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>

class HxBase;
class SoText3;

/** Class to display a legend at the upper left corner of the viewers.
    The legend is added to the root separator of the viz module the
    class is instantiated in.
*/
class HXCORE_API HxViewerLegend {

  public:

    /// Specifies where to position the legend
    enum Where {
        lowerleft =          0,
        lowerright =         1,
        upperright =         2,
        upperleft =          3 };


    /** Constructor with the @c module the Legend is instantiated in and a
        scaling factor @c s for the text size. The mean length of the
        bounding box edges is a good value for @c s.
    */
    HxViewerLegend(HxBase* module, float s);

    ///
    ~HxViewerLegend();

    /// clears the legend text in the upper left corner of the viewers
    void clearLegend();

    /** Sets @c color as text color and @ alpha as its alpha.
        If @c alpha == 0 no text will be displayed.
    */
    void setLegendColor(McColor color, float alpha = 1);

    /** Sets @c color as background color and @ alpha as its alpha.
        If @c alpha == 0 no background rectangle will be displayed.
    */
    void setLegendBackground(McColor color, float alpha = 0.333);

    /// Sets @c text as a legend into the given @c corner of the viewers
    void setLegend(const char* text, Where corner = upperleft);

    /// Sets @c text at position @pos in viewer
    void setTextAt(const McVec3f& pos, const char* text);

    /** Switches the 3D text mode.
        If on, the text from @ setTextAt is displayed in 3D in the viewers
    */
    void set3DTextMode(bool mode);

    SoFont* soFont;
    SoText3* soText;

    McVec3f textPosition;

    float textScale;
    int use3DText;
    int fontSize;
    McColor textColor;
    float   textAlpha;
    McColor bgColor;
    float   bgAlpha;

    Where whichCorner;
    McString legend;
    McDArray<McString> texts;
    McDArray<McVec3f> positions;

protected:

    HxBase* basemodule;
    float textscalefac;

    McHandle<SoSwitch> soTextRoot;
    SoMaterial* soMaterial;

};
#endif

/// @}
