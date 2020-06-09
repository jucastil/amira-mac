/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIEXTRACTORCALLBACK_H
#define  _MIEXTRACTORCALLBACK_H

/**
* @DTEXT  Abstract base class for extraction callback interfaces.
*
* @ingroup MeshIViz_Extract 
* 
* @DESCRIPTION 
* This abstract class specifies the interface used by extractors to notify the application
* when an extraction starts and stops.
* Each class implementing MiExtractorCallback must implement the beginExtractCB and endExtractCB methods. 
* 
*/
class MiExtractorCallback
{
public:
  virtual ~MiExtractorCallback() {}

  /**
  * This method is called each time a new extraction starts and only if the mesh, 
  * the cell filter, the tessellator or the data sets have changed since the last extraction.
  * @param geomChanged true if the geometry of the extracted mesh must be updated.
  * @param topoChanged true if the topology of the extracted mesh must be updated.
  * @param dataSetChanged true if the data sets associated to the extracted mesh must be updated.
  */
  virtual void beginCallback(bool geomChanged, bool topoChanged, bool dataSetChanged) = 0;

  /**
  * This method is called each time a new extraction ends and only if the mesh, 
  * the cell filters, the tessellator or the data sets have changed since the last extraction.
  * After this call, the extracted mesh has been updated and can then be parsed again to retrieve the new values.
  * @param geomChanged true if the geometry of the extracted mesh has just been updated.
  * @param topoChanged true if the topology of the extracted mesh has just been updated.
  * @param dataSetChanged true if the data sets associated to the extracted mesh has just been updated.
  */
  virtual void endCallback(bool geomChanged, bool topoChanged, bool dataSetChanged) = 0;
  
};



#endif /* _MIEXTRACTORCALLBACK_H */


