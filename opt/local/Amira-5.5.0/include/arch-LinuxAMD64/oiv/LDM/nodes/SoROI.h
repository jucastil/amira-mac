/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_ROI_
#define  _SO_ROI_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBox3i32.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoNodeSensor.h>


class SoGLRenderAction;
class SoCallbackAction;
class SoWriteAction;

/**
* @LDMEXT Region of Interest (subvolume) node.
*
* @ingroup LDMNodes
*
* @DESCRIPTION
*   The ROI ("region of interest") node allows you to specify a region of the data
*   volume that will be rendered. Voxels within the ROI are rendered; voxels outside
*   the ROI are not rendered.  In addition, voxels inside the ROI are loaded, but
*   voxels outside the ROI are not loaded.
*
*   The ROI can be a simple box (default) or a complex shape defined by (up to) three
*   box shapes (X, Y, and Z slabs) and logic flags that specify how the slabs are to
*   be combined.
*
*   You can use the ROI to get a better view of specific regions of the volume,
*   including interior regions. By reducing the number of voxels rendered, you may
*   also be able to improve performance.  By reducing the number of voxels loaded,
*   you may also be able to reduce memory requirements and/or increase image quality.
*
*   The #box and #subVolume fields are specified in voxel coordinates. The limits are included in the
*   ROI. A value of 0,0,0 0,0,0 (min and max) in the #subVolume field means that
*   this field should be ignored. This is the default.
*
*   This node acts on the rendering shape nodes of VolumeViz (SoVolumeRender, SoOrthoSlice,
*   SoObliqueSlice, SoVolumeSkin, etc.) and ReservoirViz (SoMeshLogicalSlice, SoMeshSkin  etc.)
*
*   To define a simple ROI, set the limits of the ROI in the #box field
*   (and do not set the #subVolume field). The same result is obtained by
*   setting the #box and #subVolume fields to the same value, but this is not necessary.
*
*   For a complex ROI,
*   the region defined by the SoROI #box field always acts upon the region
*   defined by the SoROI #subVolume field, not the entire volume. For example,
*   in EXCLUSION_BOX mode, the visible portion of the volume is the #subVolume
*   region minus the #box region. You are allowed to set the #box region larger
*   than (or completely outside) the #subVolume region, but only the intersection
*   of the two regions is significant.
*
*   You can also use the convenient manipulator class SoROIManip to allow your
*   users to interactively move and resize the region of interest.
*
*      @TABLE_0B
*         @TR The figure on the right shows an entire data volume.
*
*             The figures below show the #subVolume field used to limit the
*             visible portion of the volume (left) and the ROI used as an
*             "exclusion box" to cut away part
*             of the subvolume (right).
*             @TD @IMAGE roidisabled.jpg
*         @TR @IMAGE subvolume.jpg
*             @TD @IMAGE roiexclusion.jpg
*      @TABLE_END
*
*   @B The Crop Box and Cropping Process. @b
*
*   The crop box is defined by three sets of parallel planes that define three
*   slabs:
*
*   - The xmin and xmax planes define the X slab.
*   - The ymin and ymax planes define the Y slab.
*   - The zmin and zmax planes define the Z slab.
*
*   After these three planes have been specified, cropping is done in four stages.
*
*   Stage 1 determines which voxels to include relative to one or more of the slabs.
*   Classification can be enabled or disabled relative to the X slab, Y slab, or Z
*   slab. This classification is performed three separate times, resulting in three
*   terms: Term 0, Term 1, and Term 2. Each term has its own logic flags that enable
*   the three slabs, independent of the other terms. The flags are as follows:
*
*   - Enable or disable classification relative to the X slab.
*   - Enable or disable classification relative to the Y slab.
*   - Enable or disable classification relative to the Z slab.
*
*   Stage 2 determines whether to invert the values obtained in Stage 1 so that the
*   voxels @I outside @i a slab are selected. This determination is made for each
*   of the terms (Term 0, Term 1, Term 2). As in Stage 1, each term has its own
*   inversion flag and is independent of the other terms.
*
*   Stage 3 creates either the @I union @i or the @I intersection @i of Term 0,
*   Term 1, and Term 2. This is specified using a logic flag.
*
*   Stage 4 determines whether to @I invert @i the result of Stage 3 and provides
*   the final ROI. Again, the inversion (if any) is specified using a logic flag.
*
*
*
*   @B Example of Cropping Process @b
*
*   (Figures courtesy Real Time Visualization)
*
*   The following example will show you how the cropping process works.
*
*   Start with a volume that is 100x200x100 (x, y, z). The final cropped shape will
*   be the union of a 20x200x20 bar and a 100x25x100 box.
*
*   Here is the initial volume:
*
*   @IMAGE ROI_a.jpg
*
*   Here is the bar:
*
*   @IMAGE ROI_b.jpg
*
*   The bar can be formed in Term 0 of Stage 1 by using the intersection of the X and
*   Z slabs, each with min and max values set to 40 and 60, respectively.
*
*   Here is the box:
*
*   @IMAGE ROI_c.jpg
*
*   The box can be formed in Term 1 of Stage 1 by using just the Y slab, with min and
*   max values set to 125 and 150.
*
*   Term 2 of Stage 1 can be set to be identical to Term 0 or Term 1, or it can be
*   set to include no samples by setting no enable flags (no slabs selected, so
*   entire volume is selected) and setting the invert flag of Stage 2 so that the
*   entire volume is deselected. To get the union of these terms in Stage 3,
*   OR_SELECT is set. That results in the desired cropping, so Stage 4, in which the
*   results are inverted, is not used.
*
*   Here is the code to set the box dimensions and the logic flags:
*
*  @oivnetdoc
*   <PRE>
*    xmin=40; xmax=60;
*    ymin=125; ymax=150;
*    zmin=40; zmax=60;
*    myROI.box.SetValue(xmin, ymin, zmin, xmax, ymax, zmax);
*    myROI.flags.SetValue(ENABLE_X0|ENABLE_Z0|ENABLE_Y1|INVERT_2|OR_SELECT);</PRE>
*  @else
*   <PRE>
*    xmin=40; xmax=60;
*    ymin=125; ymax=150;
*    zmin=40; zmax=60;
*    myROI->box.setValue(xmin, ymin, zmin, xmax, ymax, zmax);
*    myROI->flags.setValue(ENABLE_X0|ENABLE_Z0|ENABLE_Y1|INVERT_2|OR_SELECT);</PRE>
*  @endoivnetdoc
*   Here is the resulting complex crop box:
*
*   @IMAGE ROI_d.jpg
*
*
*   @B Additional Examples @b
*
*      @TABLE_0B
*         @TR @IMAGE ROI_ex1.jpg
*           @TD @B Example 1: @b flags = SUB_VOLUME
*
*                  Alternate setting:flags = ENABLE_X0 | ENABLE_Y1 | ENABLE_Z2
*         @TR @IMAGE ROI_ex2.jpg
*           @TD @B Example 2: @b flags = FENCE
*
*                  Alternate setting:flags = ENABLE_X0 | ENABLE_Y1 |
*                                            ENABLE_Z2 | OR_SELECT
*         @TR @IMAGE ROI_ex3.jpg
*           @TD @B Example 3: @b flags = FENCE
*
*                  Note that example 2 and 3 have the same flags set;
*                  but in example 2, xmin, ymin, and zmin values are set to zero. Setting its xmax,
*                  ymax, and zmax values to the maximum value produces a similar crop.
*         @TR @IMAGE ROI_ex4.jpg
*           @TD @B Example 4: @b flags = FENCE_INVERT
*
*                  Alternate setting:flags = ENABLE_X0 |
*                                            ENABLE_Y1 | ENABLE_Z2 | OR_SELECT | INVERT_OUTPUT
*         @TR @IMAGE ROI_ex5.jpg
*           @TD @B Example 5: @b flags = CROSS
*
*                  Alternate setting:flags = ENABLE_X0 | ENABLE_Y0 |
*                                            ENABLE_Y1 | ENABLE_Z1 | ENABLE_X2 | ENABLE_Z2 | OR_SELECT
*         @TR @IMAGE ROI_ex6.jpg
*           @TD @B Example 6: @b flags = CROSS_INVERT
*
*                  Alternate setting:flags = CROSS | INVERT_OUTPUT
*      @TABLE_END
*
* @FILE_FORMAT_DEFAULT
*    ROI {
*    @TABLE_FILE_FORMAT
*       @TR subVolume   @TD 0, 0, 0, 0, 0, 0
*       @TR box         @TD 0, 0, 0, 1, 1, 1
*       @TR flags       @TD 7
*       @TR relative    @TD FALSE
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoVolumeRender,
*    SoOrthoSlice,
*    SoObliqueSlice,
*    SoROIManip
*
* @ACTION_BEHAVIOR
* SoCallbackAction,
* SoGLRenderAction,
* SoGetBoundingBoxAction,
* SoPickAction,
* SoWriteAction
*
*
*/
class LDM_API SoROI : public SoNode {
  SO_NODE_HEADER( SoROI );

 public:
  /**
   * Specifies the bounds of the region of interest. If #subVolume is non-empty,
   * the box is clamped at the bounds of the subvolume. Depending on the
   * #relative field, the bounds may be relative to the subvolume. Default is
   * an (essentially) empty box.
   */
  SoSFBox3i32 box;

  /**
   * Specifies how the bounds of the box are used. Default is SUB_VOLUME. The region of
   * interest is the box itself.
   */
  SoSFBitMask flags;

  /**
   * Flag value mask
   */
  enum Flags {
    /** Enable cropping with X slab for term 0 (stage 1) */
    ENABLE_X0 = 0x1,
    /** Enable cropping with Y slab for term 0 (stage 1) */
    ENABLE_Y0 = 0x2,
    /** Enable cropping with Z slab for term 0 (stage 1) */
    ENABLE_Z0 = 0x4,
    /** Invert result for this term 0 (stage 2) @BR */
    INVERT_0  = 0x8,

    /** Enable cropping with X slab for term 1 (stage 1) */
    ENABLE_X1 = 0x10,
    /** Enable cropping with Y slab for term 1 (stage 1) */
    ENABLE_Y1 = 0x20,
    /** Enable cropping with Z slab for term 1 (stage 1) */
    ENABLE_Z1 = 0x40,
    /** Invert result for this term 1 (stage 2) @BR */
    INVERT_1  = 0x80,

    /** Enable cropping with X slab for term 2 (stage 1) */
    ENABLE_X2 = 0x100,
    /** Enable cropping with Y slab for term 2 (stage 1) */
    ENABLE_Y2 = 0x200,
    /** Enable cropping with Z slab for term 2 (stage 1) */
    ENABLE_Z2 = 0x400,
    /** Invert result for this term 2 (stage 2) @BR */
    INVERT_2  = 0x800,

    /**
     * Stage 3: If set, the result is the union (OR) of term 0, term 1, and term 2. If
     * clear, the result is the intersection (AND) of the three terms @BR
     */
    OR_SELECT     = 0x1000,

    /**
     * Stage 4: If enabled, the result of stage 4 (union or intersection) is inverted
     * as the last step in cropping @BR
     */
    INVERT_OUTPUT = 0x2000,

    /** Convenient enums */
    SUB_VOLUME    = ENABLE_X0 | ENABLE_Y0 | ENABLE_Z0,
    EXCLUSION_BOX = SUB_VOLUME | INVERT_OUTPUT,
    CROSS         = ENABLE_X0 | ENABLE_Y0 | ENABLE_Y1 | ENABLE_Z1 | ENABLE_X2 | ENABLE_Z2 | OR_SELECT,
    CROSS_INVERT  = CROSS | INVERT_OUTPUT,
    FENCE         = ENABLE_X0 | ENABLE_Y1 | ENABLE_Z2 | OR_SELECT,
    FENCE_INVERT  = FENCE | INVERT_OUTPUT
  };

  /**
   * Specifies the bounds of the subvolume that will be rendered. By default, it is an
   * empty box and has no effect. The subvolume is always a simple box.
   */
  SoSFBox3i32 subVolume;

  /**
   * Specifies whether the box bounds are relative to the subvolume or the full volume
   * (i.e., are specified in absolute slice coordinates). TRUE means that if the
   * subvolume is non-empty, moving the subvolume through the volume also moves the
   * ROI box through the volume. Default is FALSE.
   */
  SoSFBool  relative;

  /**
   * Constructor.
   */
  SoROI();

 SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void pick(SoPickAction *action) ;
  virtual void write(SoWriteAction *action);


  //------------------------------------------------------------------------------

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**
   * Return the list of all visible boxes
   * @param boxes is the list of visible boxes
   * @param dim is the volume ijk dimension
   * @return the nimber of element in boxes
   */
  int getVisibleBoxes(SbBox3i32* &boxes, const SbVec3i32 &dim);

  /**
   * Compute the bounding box enclosing all visible boxes
   * @param box is the bounding box enclosing all visible boxes
   * @param dim is the volume ijk dimension
   */
  void getVisibleBoundingBox(SbBox3i32& box, const SbVec3i32 &dim);

  virtual SoNode* getAlternateRep( SoAction* action );

 protected:
  // Destructor
  virtual ~SoROI();

 private:
  SoNodeSensor  *m_FiedsNS;
  int            m_NumVisBoxes;
  SbBox3i32     *m_VisBoxes;
  SbVec3i32      m_dim;
  unsigned int   getVisibleParts();
  static void    fieldsChangedCB(void *, SoSensor *);

};
//--------------------------------------------------------------------------------

#endif // _SO_ROI_
