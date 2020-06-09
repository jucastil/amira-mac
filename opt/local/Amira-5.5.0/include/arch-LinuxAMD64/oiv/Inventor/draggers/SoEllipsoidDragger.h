/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Jan 2008)
**=======================================================================*/

#ifndef _SO_ELLIPSOID_DRAGGER_H_
#define _SO_ELLIPSOID_DRAGGER_H_

#include <Inventor/draggers/SoTabPlaneDragger.h>

class SoFieldSensor;
class SoSwitch;

/**
* Ellipsoid you can translate or scale within a plane by dragging with the mouse.
* 
* @ingroup draggers
* 
* @DESCRIPTION
*   SoEllipsoidDragger is derived from SoTabPlaneDragger and has similar behavior.
*   The difference is that the displayed shape is an ellipsoid that fills the
*   extent of the dragger.
*
*   If you set the #constrained field to TRUE, the edge tabs are hidden (only
*   corner tabs are visible) and scaling is uniform.
*
*   The #numSamples field specifies the number of points used to draw the ellipsoid.
*   You can ensure the displayed shape is a circle if you set the #constrained field to TRUE
*   before any scaling is applied.
*
*   The scaleUniform and lineWidth fields inherited from SoTabPlaneDragger are ignored.
*
* @FILE_FORMAT_DEFAULT
*    EllipsoidDragger {
*    @TABLE_FILE_FORMAT
*       @TR renderCaching        @TD AUTO
*       @TR boundingBoxCaching   @TD AUTO
*       @TR renderCulling        @TD AUTO
*       @TR pickCulling          @TD AUTO
*       @TR isActive             @TD FALSE
*       @TR resizeHandles        @TD FALSE
*       @TR translation          @TD 0 0 0
*       @TR scaleFactor          @TD 1 1 1
*       @TR numSamples           @TD 100
*       @TR constrained          @TD FALSE
*       @TR scaleUniform         @TD FALSE
*       @TR twoSidedLighting     @TD FALSE
*       @TR lineWidth            @TD 1
*       @TR callbackList         @TD NULL
*       @TR translator           @TD \<tabPlaneTranslator resource\>
*       @TR scaleTabMaterial     @TD \<tabPlaneScaleTabMaterial resource\>
*       @TR scaleTabHints        @TD \<tabPlaneScaleTabHints resource\>
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoInteractionKit,
*    SoDragger,
*    SoCenterballDragger,
*    SoDirectionalLightDragger,
*    SoDragPointDragger,
*    SoHandleBoxDragger,
*    SoJackDragger,
*    SoPointLightDragger,
*    SoRotateCylindricalDragger,
*    SoRotateDiscDragger,
*    SoRotateSphericalDragger,
*    SoScale1Dragger,
*    SoScale2UniformDragger,
*    SoScaleUniformDragger,
*    SoSpotLightDragger,
*    SoTabBoxDragger,
*    SoTabPlaneDragger,
*    SoTrackballDragger,
*    SoTransformBoxDragger,
*    SoTransformerDragger,
*    SoTranslate1Dragger,
*    SoTranslate2Dragger
* 
* 
* 
*/ 

class INVENTOR_API SoEllipsoidDragger : public SoTabPlaneDragger 
{

  SO_KIT_HEADER(SoEllipsoidDragger);

  public:

    /**
    * Constructor.
    */
    SoEllipsoidDragger();

    /**
    * Number of samples composing the ellispoid.
    * 
    */
    SoSFInt32 numSamples;

    /**
    * Hint about constrained scaling. 
    * 
    */
    SoSFBool constrained;

    SoINTERNAL public:
    static void         initClass();    // initialize the class
    static void         exitClass();

  protected:

    virtual ~SoEllipsoidDragger();

    //Sample circle
    void sample( int numSamples );

    // Sensor associated with numSamples field
    SoFieldSensor *numSamplesFieldSensor;

    // Sensor callback
    static void numSamplesFieldSensorCB( void *, SoSensor * );

    //sensor associated with constrained field
    SoFieldSensor *constrainedFieldSensor;

    // Sensor callback
    static void constrainedFieldSensorCB( void *, SoSensor * );
};

#endif //_SO_ELLIPSOID_DRAGGER_H_
