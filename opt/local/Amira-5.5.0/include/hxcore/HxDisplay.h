/*==============================================================================
 *   File        : HxDisplay.h
 *   Classes     : HxDisplay
 *   Author(s)   : G.TALLEC
 *   Date        : May 2007
 *==============================================================================
 *  OpenInventor (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S. All rights reserved
 *==============================================================================
 *
 * Description : class managing display properties :
 *               - shadowing
 *               - projection
 *
 *============================================================================*/

#ifndef HX_DISPLAY_H
#define HX_DISPLAY_H

#include <hxcore/HxConnection.h>
#include <hxcore/HxBoundingBox.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFloatTextN.h>

#include <hxcore/SoTabBoxDraggerVR.h>

#include <Inventor/SbLinear.h>
class HxModule;

class SbProjection;
class SoProjection;
class SoShadowStyle;
class SoGroup;

class HXCORE_API HxDisplay 
{

  public:

    /// Constructor
    HxDisplay();

    /// Constructor
    HxDisplay( HxModule *module, bool enableProj, bool enableShadowing, bool enableBox=false );

    /// Destructor
    virtual ~HxDisplay();

    /// Enable the projection for the given module
    void enableProjection( HxModule *module, bool enable);

    /// says if projection is enabled
    bool isProjectionEnabled(){return m_projectionEnabled; }

    /// says if box is active (checked)
    bool isBoxActive();

    /// says if projection is active (connected)
    bool isProjectionActive();

    /// connection to projection
    void connectToProjectionModule( bool connect );

    /// set active projection
    void setInternalProjection( SoProjection* projNode );

    /// return active projection routine
    SbProjection* getInternalProjection();

    /// return active projection node
    SoProjection* getInternalProjectionNode();

    /// return active projection
    SbProjection* getInternalProjection( bool &portIsNew );

    /// return new state projection flag
    bool getProjectionNewState();

    /// Connection to projection module
    HxConnection *portProjection;

    /// change shadow style
    void shiftShadowStyle();

    /// set if module can impact shadowing
    void enableShadowing( bool enable );

    /// says if module can impact shadowing
    bool isShadowingEnabled(){return m_shadowingEnabled;}

    /// shadow stuffs initialisation
    virtual void initShadowing( SoGroup *root );

    /// Returns the shadow style node  
    SoShadowStyle* getShadowStyle() const { return m_shadowStyle; }

    //----  seed box -------------------------------------------

    // Seed box is used to see a bounding box.

    // We use a SoTabBoxDraggerVR to get the behavior combined with a hxBoundingBox 
    // to get the correct shape.
    // We cant use a  projected SoTabBoxDraggerVR since SoTransform node are not compatible with a projection

    /// port Box
    HxPortGeneric *portBox;

    /// BBox center 
    HxPortFloatTextN *portBoxCenter;

    /// BBox scale factor 
    HxPortFloatTextN *portBoxScaleFator;

    /// Enable the box for the given module
    void enableBox( HxModule *module, bool enable);

    void defaultTransform( SbVec3f& trans, SbVec3f& scale );

    /// Fill values from port
    void getDraggerValuesFromPort( SbVec3f &trans, SbVec3f &scale );

    void updateBoxDragger();

    /// Update box dragger after a port modification
    bool updateBoxFromPort();

    /// update dragger geometry from ports. Return invalid value hint
    bool updateBoxFromRealDraggerValues( SbVec3f &trans, SbVec3f &scale );

    void updatePortFromBox( SbVec3f &trans, SbVec3f &scale );

    /// get values of boxDragger in real coordinates
    void getRealBoxDraggerValues( SbVec3f &trans, SbVec3f &scale );

    /// set dragger values
    void setDraggerValues(SbVec3f &trans, SbVec3f &scale);

    void setFieldBoundingBox(float *bbox){ for(int i=0;i<6;i++) m_bbox[i] = bbox[i];}

    /// create the seed box
    void createBox();

    /// check if the seed box has changed
    bool checkBox( bool computeDraggerValues = true);

    /// make the seed box visible
    void showBox();

    /// check if portBox is new
    bool updatePortBox();

    /// hide the seed box 
    void hideBox();

    /// Dragger
    SoTabBoxDraggerVR* m_boxDragger;

    /// Dragger separator
    SoSeparator* m_boxSeparator;

    /// last projection
    SbProjection* m_lastProjection;

    float *getDraggerBBox(){return m_draggerBbox;}

    float m_bbox[6];

    /// bouding box
    float m_draggerBbox[6];

    // bounding box used for dragger shape
    HxBoundingBox* m_hxBB;

    //------------------------------------------------------------

protected:

  /// This node holds the shadow style of the module
  SoShadowStyle* m_shadowStyle;

  /// projection enabled state
  bool m_projectionEnabled;

  /// shadow enabled state
  bool m_shadowingEnabled;

  /// box enabled state
  bool m_boxEnabled;
    
  /// projection new state flag : is new if newly projected or newly unprojected
  bool m_projectionNewState;

  /// module controlled
  HxModule *m_module;

  SbProjection* m_projection;

  //Stored projection routine
  SoProjection* m_projectionNode;

  void commonConstructor();
};

#endif

