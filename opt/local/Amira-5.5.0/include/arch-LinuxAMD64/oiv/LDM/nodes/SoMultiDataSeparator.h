/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_MULTI_DATA_SEPARATOR_H
#define SO_MULTI_DATA_SEPARATOR_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/SoLDMMediator.h>
#include <LDM/elements/SoDataSetElement.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/STL/set>

/**
* @LDMEXT Separator for combining multiple data sets
* @ingroup LDMNodes
*
* @DESCRIPTION
*
* The SoMultiDataSeparator node allows you to combine multiple data sets.
*
* This is the correct method for combining multiple data sets. Combining
* multiple data sets without inserting them under an SoMultiDataSeparator
* node may produce incorrect results and should be avoided.
*
* All data sets below this node belong to the same group for subsequent
* multidata combining operations.
* Each data set is represented by an SoDataSet node (typically an SoVolumeData node).  
* Combining is enabled by an SoDataCompositor node for CPU combining or
* an SoVolumeShader node for GPU combining.  A common use of GPU combining is to
* implement co-blending of multiple volumes, in other words using a fragment shader
* to combine the color and/or intensity values of the voxels.
*
* @B NOTE @b @BR
* All SoDataSet objects under the same SoMultiDataSeparator:
* - Must have a unique ID (see SoDataSet::dataSetId).
* - Must share a set of common properties :
*   - Volume dimensions (number of voxels in X, Y, and Z)
*   - Tile size
*   - Tile overlap (aka border)
*
* GPU combining must be implemented in a shader program written in the standard GLSL language.
* The shader program will be specified using an SoVolumeShader node.  The shader source code
* is loaded using (for example) an SoFragmentShader object. Uniform parameters for the
* shader may be specified using the subclasses of SoShaderParameter. See SoVolumeShader for
* more information about the shader function library provided by VolumeViz.
*
* For each data set there will typically be an SoDataRange node and an SoTransferFunction 
* node to define the mapping from data values to color values.
* For each SoVolumeData a separate 3D texture will be generated and sent to the GPU.
* 3D textures can be generated with different precision (8-bit or 12-bit) according to 
* the SoDataSet::texturePrecision field.  The texture unit used for each data set is
* determined by the SoDataSet::dataSetId field.
* All colormaps are aggregated into a single 2D texture.
*
* A custom fragment shader can retrieve the voxel's data value from each 3D texture 
* using the GLSL VolumeViz function:
* \code
*               VVIZ_DATATYPE value = VVizGetData( dataSetId, texCoord );
* \endcode
* A custom fragment shader can lookup the color/intensity for each data value from
* the appropriate colormap, using the GLSL VolumeViz function:
* \code
*               vec4 color = VVizTransferFunction( value, colorMapId );
* \endcode
* A custom fragment shader can then compute (using custom blending functions) the actual
* color for the voxel and output that color using the GLSL VolumeViz function:
* \code
*               VVizOutputColor( color ):
* \endcode
*
* @EXAMPLE
* The following code shows how to do multidata rendering using an
* SoVolumeShader node to combine values for an SoVolumeRender node.
* Given two SoVolumeData nodes ds1 and ds2:
*
* \oivnetdoc
* \code
*   dataSet1.dataSetId.SetValue(0);
*   dataSet2.dataSetId.SetValue(1);
*
*   SoMultiDataSeparator mds = new SoMultiDataSeparator();
*   mds.AddChild(volumeShader);
*   mds.AddChild(dataSet1);
*   mds.AddChild(dataSet2);
*   mds.AddChild(dataRange1);
*   mds.AddChild(dataRange2);
*   mds.AddChild(colorMap1);
*   mds.AddChild(colorMap2);
*   mds.AddChild(new SoVolumeRender());
*
*   root.AddChild(mds);
* \endcode
* \else
* \code
*   dataSet1->dataSetId = 0;
*   dataSet2->dataSetId = 1;
*
*   SoMultiDataSeparator* mds = new SoMultiDataSeparator();
*   mds->addChild(volumeShader);
*   mds->addChild(dataSet1);
*   mds->addChild(dataSet2);
*   mds->addChild(dataRange1);
*   mds->addChild(dataRange2);
*   mds->addChild(colorMap1);
*   mds->addChild(colorMap2);
*   mds->addChild(new SoVolumeRender);
*
*   root->addChild(mds);
* \endcode
* \endoivnetdoc
*
* @SEE_ALSO
* SoDataSet, SoVolumeData, SoDataCompositor, SoVolumeShader
*
*
*/
class LDM_API SoMultiDataSeparator : public SoSeparator {
  SO_NODE_HEADER(SoMultiDataSeparator);

public:

 /**
  * Constructor.
  */
  SoMultiDataSeparator();

SoEXTENDER public:
  /**
  * Return the mediator of this node
  */
  SoLDMMediator *getMediator() { return &m_mediator; }

  virtual void GLRender(SoGLRenderAction *action);
  virtual void GLRenderBelowPath(SoGLRenderAction *action);
  virtual void GLRenderInPath(SoGLRenderAction *action);
  virtual void GLRenderOffPath(SoGLRenderAction *action);
  virtual void doAction(SoAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void write(SoWriteAction *action);

SoEXTENDER_Documented public:
  /**
  * Returns a reference to an LDMManagerAccess.
  */
  SoLDMMediator::LDMManagerAccess &getLdmManagerAccess() { return m_mediator.ldmManagerAccess; }

protected:
  virtual ~SoMultiDataSeparator();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**Remove the given dataset*/
  void remove(SoDataSet* ds);

  /** Remove all handled data sets from LDM loading threads. */
  void removeFromLdm();

  /** Clear the list of handled dataset */
  void reset();

private:
  typedef std::set<SoLDM::DataSetIdPair> DsSet;

  void updateDatasets();
  void updateDatasetList(const SoLDM::DataSetIdPairList &newDsList);
  //Search for all dataset in the subgraph
  void getDatasets(SoLDM::DataSetIdPairList &dsList, SoNode *subGraph) const;
  bool hasListChanged(const SoLDM::DataSetIdPairList &newDsList) const;

  //Return datasets whose id has already been assigned
  void findDuplicatedId(DsSet &dsDup, const SoLDM::DataSetIdPairList &dsList) const;
  bool isInSet(const DsSet &dsSet, const SoLDM::DataSetIdPair& p) const;

  //Result contains a-b.
  template<typename Container1, typename Container2>
  void getDsListDifference(SoLDM::DataSetIdPairList &result, const Container1 &a, const Container2 &b) const;

  //If ds from dsList has already a MultiDataSeparator, remove it
  //and add it to the m_mutipleRefDsList of the other group.
  void removeFromAssignedGroup(const SoLDM::DataSetIdPairList &dsList);

  //Ignore this DS next time the ds list change
  void addToMutipleRefDsList(const SoLDM::DataSetIdPair& p);
  //Print an error message if a ds is in more than one SoMultiDataSeparator
  void checkForDSInOtherGroups();

  //Unregister from mediator given ds list
  void unregisterDs(const SoLDM::DataSetIdPairList &dsToRemove);

  //Register from mediator given ds list
  void registerDs(const SoLDM::DataSetIdPairList &dsToRegister);

  SoLDMMediator m_mediator;
  SoLDM::DataSetIdPairList m_dsList;
  SoLDM::DataSetIdPairList m_mutipleRefDsList;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
