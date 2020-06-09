/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : M.LEBORGNE (Aug 2002)
**=======================================================================*/

#ifndef _SO_APPEARANCE_PRESERVER_
#define _SO_APPEARANCE_PRESERVER_

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbLinear.h>

class SoTexture2 ;
class SoTextureCoordinate2 ;
class SoNode ;
class APSTriObject ;
class APS ;

/**
 * @FXEXT Encapsulates an appearance preserving simplification algorithm.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 * This technique computes, from a highly detailed model and its corresponding
 * simplified model
 * obtained with the decimation tools (see SoSimplifyAction, SoSimplify...), a
 * normal map texture and texture coordinates for this texture to be applied to
 * the simplified model.
 * For each triangle in the simplified model, there is a triangular area in the
 * normal map texture that contains normal vectors derived from the original
 * complex model.
 * Using the bump mapping technique with the generated normal map, 
 * the rendering of the simplified model will appear with the details of
 * the original model but using much fewer triangles.
 * 
 * @B Note 1@b: The time for generating the normal map depends on the size
 * of the original model,
 * the size of the simplified model, and also the size of the normal map texture.
 * This process could take several minutes.
 *
 * @B Note 2@b: The quality of the final rendering using the bump mapping technique is closely
 * linked to the size of the normal map texture.
 *
 * @B  Limitations@b: The size of the normal map texture limits the number of possible triangles
 * for the simplified model. This is because the minimum size for a triangle in the
 * normal map texture is at least 3 pixels. So for a 256*256 texture size, a maximum of
 * 22,000 triangles can be stored. If necessary, specify a larger texture 
 * (see #setTextureSize) or a more aggressive simplification of the model.
 *
 * @SEE_ALSO
 *   SoBumpMappingProperty, SoTextureUnit.
 * 
 */ 

class FXVIZ_API SoAppearancePreserver
{
 public:
  
  /**
   * Progress callback prototype.
   */
  typedef void SoAppearancePreserverProgressCB(void *userData, 
                                               SoAppearancePreserver *aps, 
                                               int percent);
  
  /**
   * Constructor.
   */
  SoAppearancePreserver();

  /**
   *  Destructor.
   */
  ~SoAppearancePreserver();
  
  /**
   * Specifies the original scene graph and the simplified scene graph.
   *
   */
  void setSceneGraphs(SoNode *original, SoNode *simplified);

  /**
   * Specifies the texture size to be generated. If the specified dimensions
   * are not powers of two, the nearest powers of two will be used.
   * Default size is 256 * 256 texels.
   */
  void setTextureSize(int width, int height);

  /**
   * Specifies the mininum size for a triangle stored within the normal map texture.
   * Default size is 4 texels.
   */
  void setTriangleMinSize(int size);

  /**
   * Sets a progress callback.
   * This callback will be called at each percentage of completion, e.g., 1%, 2%...
   * 
   */
  void setProgressCallback(SoAppearancePreserverProgressCB *cb, void *data=NULL);
  
  /**
   * Computes the normal map texture and creates an SoTexture2 node.
   * If no file name is specified, the texture is stored in the SoTexture2 
   * @B image@b field. Otherwise the file name is stored in the SoTexture2 
   * @B filename@b field and the texture is written to a PNG format file.
   * NULL is returned if the texture could not be computed, generally
   * due to there being more triangles than could be stored in the normal map.
   *
   * @UNICODE_WARNING
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  SoNONUNICODE SoTexture2*           getNormalMapTexture(const char *filename=NULL);

  /**
   * Computes the normal map texture and creates an SoTexture2 node.
   * If no file name is specified, the texture is stored in the SoTexture2 
   * @B image@b field. Otherwise the file name is stored in the SoTexture2 
   * @B filename@b field and the texture is written to a PNG format file.
   * NULL is returned if the texture could not be computed, generally
   * due to there being more triangles than could be stored in the normal map.
   *
   */
  SoTexture2*           getNormalMapTexture( const SbString& filename = "" );

  /**
   * Computes the displacement map texture and creates an SoTexture2 node.
   * If no file name is specified, the texture is stored in the SoTexture2 
   * @B image@b field. Otherwise the file name is stored in the SoTexture2 
   * @B filename@b field and the texture is written to a PNG format file.
   * NULL is returned if the texture could not be computed, generally
   * due to there being more triangles than could be stored in the normal map.
   *
   * @UNICODE_WARNING
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  SoNONUNICODE SoTexture2*           getDisplacementMapTexture(const char *filename=NULL);

  /**
   * Computes the displacement map texture and creates an SoTexture2 node.
   * If no file name is specified, the texture is stored in the SoTexture2 
   * @B image@b field. Otherwise the file name is stored in the SoTexture2 
   * @B filename@b field and the texture is written to a PNG format file.
   * NULL is returned if the texture could not be computed, generally
   * due to there being more triangles than could be stored in the normal map.
   * 
   */
  SoTexture2*           getDisplacementMapTexture( const SbString& filename = "" );

  /**
   * Computes the texture coordinates and creates an SoTextureCoordinate2 node.
   * The texture coordinates are stored in the texture coordinate @B point@b field.
   * They can be applied with the bump mapping technique to the simplified model.
   * NULL is returned if the texture coordinates could not be computed, generally
   * due to there being more triangles than could be stored in the normal map.
   *
   */
  SoTextureCoordinate2* getBumpCoords();
  
 private:
  // To remove - prototype
  // Must be suppressed in the futur.
  // Generate a Bump Mapping format (defined by Frederic Fratani before integration)
  APSTriObject * getBumpObject();
  
  APS          *m_aps;
  APSTriObject *m_apsHighLevel;
  APSTriObject *m_apsLowLevel;
  
  // Callbacks.
  static void progressCB(int percent, void * data);
  SoAppearancePreserverProgressCB   *m_callback;
  void                              *m_userData;
};

#endif /* _SO_APPEARANCE_PRESERVER_ */
