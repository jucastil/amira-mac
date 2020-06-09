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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_WIDGET_TEXT_H_
#define _VS_WIDGET_TEXT_H_


#include "Vs.h"
#include "VsWidget.h"

#include <mclib/McVec2i.h>
#include <mclib/McVec4f.h>

#include <mcgl/McGLText.h>

// VS_RELAY_CLASS VsWidgetText VsWidgetRelay


class VSVOLREN_API VsWidgetText : public VsWidget
{
    VS_DECL_INTERFACE        ( VsWidgetText )
    VS_DECL_INTERFACE_IMPL   ( VsWidgetText )
    VS_DECL_INTERFACE_FACTORY( VsWidgetText )
    VS_DECL_INTERFACE_RELAY  ( VsWidgetText )
    
public:

    ////////////////////////////////////////
    // VsNode overrides
    ////////////////////////////////////////

    virtual VsRenderResult render();

    VSRESULT cleanup();


    ////////////////////////////////////////
    // VsWidget overrides
    ////////////////////////////////////////

    virtual void setGeometry( McVec2i & inUpperLeft, McVec2i & inSize );

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

    virtual const char * text();
    virtual VSRESULT setText( const char * inText );

    virtual McVec4f  shadowColor() const;
    virtual VSRESULT setShadowColor( const McVec4f & inColor );

    virtual McVec4f  color() const;
    virtual VSRESULT setColor( const McVec4f & inColor );

    virtual McVec4f  backgroundColor() const;
    virtual VSRESULT setBackgroundColor( const McVec4f & inColor );

    virtual McGLText::Alignment hAlignment();
    virtual VSRESULT setHAlignment( McGLText::Alignment inHAlign );

    virtual McGLText::Alignment vAlignment();
    virtual VSRESULT setVAlignment( McGLText::Alignment inVAlign );

    virtual int fontSize();
    virtual VSRESULT setFontSize( int inSize );

    virtual const char * fontFamily();
    virtual VSRESULT setFontFamily( const char * inFamily );

    virtual bool italics() const;
    virtual VSRESULT setItalics(bool inItalics);

    virtual bool bold() const;
    virtual VSRESULT setBold(bool inBold);
};


#endif

/// @}
