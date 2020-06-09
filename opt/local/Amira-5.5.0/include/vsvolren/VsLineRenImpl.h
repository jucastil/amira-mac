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
#ifndef _VS_LINERENIMPL_H_
#define _VS_LINERENIMPL_H_

#include "Vs.h"
#include "VsLineRen.h"
#include "VsLineSet.h"
#include "VsNode.h"
#include "VsNodeImpl.h"
#include "VsCropRegion.h"
#include "VsColorMap.h"
#include "VsTechniqueGLSL2.h"

#include <mclib/McColor.h>

class VsLineRenImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsLineRenImpl, VsNodeImpl, VsLineRen )

private:

    /**
    * \brief Private class which is used to store all data and states of a linset
    */
    class  VsLineSetRecord {
        public:
            VsLineSetRecord():
                color(McColor(1.f,1.f,1.f)), // default color is white
                colorMode(VsLineRen::CMODE_CONSTANT),
                colorMap(0),
                minDataWindow(0.f),
                maxDataWindow(1.f),
                lineWidth(1.f),
                visible(true),
                lighting(false),
                lineSmoothing(false),
                colorsDirty(true),
                tangentsDirty(true)
            {}

            // clear lineset record
            void clear()
            {
               // reset lineset pointer
               lineSet = 0;
               // clear color and tangents arrays
               lineColor.clear();
               tangents.clear();

               // set defaults
               color = McColor(1.f,1.f,1.f);
               colorMode = VsLineRen::CMODE_CONSTANT;
               colorMap = 0;
               minDataWindow = 0.f;
               maxDataWindow = 1.f;
               lineWidth = 1.f;
               visible = true;
               lighting = false;
               lineSmoothing = false;
               colorsDirty = true;
               tangentsDirty = true;
            };

            // constant color
            McColor color;
            // the lineset
            McHandle<VsLineSet> lineSet;

            // color array for each line of the lineset
            McDArray< McDArray<float> > lineColor;
            // tangent array for each line of the lineset
            McDArray< McDArray<McVec3f> > tangents;
            // the color mode to render a line set
            VsLineRen::ColorMode colorMode;
            // the color map for a lineset
            VsColorMap *colorMap;
            // data window
            float minDataWindow;
            float maxDataWindow;
            float lineWidth;
            // flags
            bool visible;
            bool lighting;
            bool lineSmoothing;
            bool colorsDirty;
            bool tangentsDirty;
    };

public:

    /**
    * \brief Add a lineset.
    *   Be carefull, that the lineset is not naturally append at the end of managed linesets.
    *   It is possible that the lineset is inserted, thus the index of the lineset is returned
    *
    * \param inLineSet the lineset to append
    * \return index of the appended lineset
    */
    int addLineSet( VsLineSet * inLineSet);

    /**
    * \brief Remove a lineset.
    *
    * \param iLineSet lineset to remove
    * \return
    */
    VSRESULT removeLineSet(int iLineSet);

    /**
    * \brief Set a lineset to list of linesets managed by this render node
    *
    * \param inLineSet the lineset to add
    * \param inIndex the index of the lineset
    * \return
    */
    VSRESULT setLineSet( VsLineSet * inLineSet, int iLineSet = 0 );

    /**
    * \brief Get a lineset from the render node
    *
    * \param inIndex index of a lineset
    * \return pointer to a VsLineSet object managed by this render node. In case of an error a NULL pointer is returned
    */
    virtual VsLineSet * vimpl_lineSet( int iLineSet = 0 );

    /**
    * \brief Get the number of managed linesets
    *
    * \retrun Number of current managed linesets
    */
    virtual int vimpl_numLineSets() const;

    /**
    * \brief Deletes all managed linesets by this node
    *
    * \return
    */
    virtual VSRESULT vimpl_clearLineSets();

    /**
    * \brief Toggle the visability of a lineset
    *
    * \param inFlag toggle on / off
    * \param iLineSet the line set to toggle
    * \return
    */
    VSRESULT setLineSetVisible(int iLineSet , bool inFlag);

    /**
    * \brief Check if a lineset is visible
    *
    * \param iLineSet lineset to check
    * \return true if visible else false
    */
    bool lineSetVisible(int iLineSet = 0) const;

    /**
    * \brief Set a constant color for a linset
    *
    * \param iLineSet lineset which should be set to constant color
    * \param color the color to be set
    * \return
    */
    VSRESULT setColor(int iLineSet, const McColor& color);

    /**
    * \brief Get uniform color of a lineset
    *
    * \param iLineSet lineset
    * \return uniform color of the lineset
    */
    McColor color(int iLineSet) const;

    /**
    * \brief Set a colormap for a certain lineset
    *
    * \param iLineSet index of the lineset to set a colormap
    * \param colorMap the colormap
    * \return
    */
    VSRESULT setColorMap(int iLineSet, VsColorMap *colorMap);

    /**
    * \brief Get the current colormap used by a certain lineset
    *
    * \param iLineSet index of the lineset to get the currently used colormap
    * \return the colormap
    */
    VsColorMap* colorMap(int iLineSet);

    /**
    * \brief Set the color mode of a lineset
    *
    * \param iLineSet index of a lineset to set the color mode
    * \param cmode the color mode
    * \return
    * \sa ColorMode
    */
    VSRESULT setColorMode(int iLineSet, VsLineRen::ColorMode cmode);

    /**
    * \brief Get the color mode of a lineset
    *
    * \param iLineSet index of a lineset
    * \return the color mode of the lineset
    * \sa ColorMode
    */
    VsLineRen::ColorMode colorMode(int iLineSet) const;

    /**
    * \brief Set the data window for a lineset
    *
    * \param iLineSet index of a lineset to set a data window
    * \param vmin the min value
    * \param vmax the max value
    * \return
    */
    VSRESULT setDataWindow(int iLineSet, float vmin, float vmax);

    /**
    * \brief Get the min value of the current data window
    *
    * \param iLineSet index of a lineset
    * \return the min value
    */
    float dataWindowMin(int iLineSet) const;

    /**
    * \brief Get the max value of the current data window
    *
    * \param iLineSet index of a lineset
    * \return the max value
    */
    float dataWindowMax(int iLineSet) const;

    /**
    * \brief Enable line illumination
    *
    * \param iLineSet lineset to illuminate
    * \param inFlag toggle on/off
    * \return
    */
    VSRESULT setLightingEnabled(int iLineSet, bool inFlag);

    /**
    * \brief Line illumination enabled
    *
    * \param iLineSet lineset to check illumination
    * \return true if illumination is enabled else false
    */
    bool lightingEnabled(int iLineSet) const;

    /**
    * \brief Set line width for a lineset
    *
    * \param iLineSet index of the lineset
    * \param width line width
    * \return
    */
    VSRESULT setLineWidth(int iLineSet, float width);

    /**
    * \brief Get the current line width of a lineset
    *
    * \param iLineSet index of the lineset
    * \return the line width
    */
    float lineWidth(int iLineSet) const;

    /**
    * \brief Toggle line smoothing on/off for a lineset
    *
    * \param iLineSet index of the lineset
    * \param inFag if set true smoothing is turned on
    * \return
    */
    VSRESULT setLineSmoothingEnabled(int iLineSet, bool inFlag);

    /**
    * \brief Check if line smoothing is enabled for a given lineset
    *
    * \param iLineSet index of the linset
    * \return true if smoothing is enabled else false
    */
    bool lineSmoothingEnabled(int iLineSet) const;

    /** 
    * Sets a new crop region. If a crop region is active only the
    * parts line parts inside the crop region will be shown.
    * In order to disable cropping you should call this method with
    * a zero pointer. The crop region object will not
    * be copied but a handle to the object will be stored. When
    * the crop region is modified, this object will be automatically
    * touched. 
    * \param  inCropRegion
    *         New crop region. If zero, cropping is disabled.
    * \return 
    *         If the method succeeds, the return value is #VS_OK. To get 
    *          extended error information, call Vs::lastError().
    */
    VSRESULT setCropRegion( VsCropRegion * inCropRegion );

    /** Returns the current crop region object. 
        \return Current crop region or zero if cropping is disabled.
    */
    VsCropRegion * cropRegion() const;

public:

    /// overloaded functions from VsNode
    virtual VsRenderResult vimpl_render();
    virtual VSRESULT vimpl_cleanup();
    virtual VSRESULT vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );

private:

    // managed linesets
    McDArray<VsLineSetRecord> mLineSets;

    // handle glsl
    McHandle<VsTechnique2> mTechnique;
    McHandle<VsTechnique2::Params2> mParams;
    // attached crop region
    McHandle<VsCropRegion> mCropRegion;

    int mId_LIGHTDIR;
    int mId_AMBIENT;
    int mId_DIFFUSE;

    void drawLines(VsLineSetRecord &lineSetRecord); // draw vertex arrays
    void calculateDecColors(VsLineSetRecord &lineSetRecord); // calculate direction encoded color arrays
    VSRESULT calculateColors(VsLineSetRecord &lineSetRecord, int iDataValue); // calculate dataValue depending color arrays by using the datawindow and colormap
    void calculateTangents(VsLineSetRecord &lineSetRecord); // calculate tangent arrays for every line of the line set
};

#endif //_VS_LINERENIMPL_H_

/// @}
