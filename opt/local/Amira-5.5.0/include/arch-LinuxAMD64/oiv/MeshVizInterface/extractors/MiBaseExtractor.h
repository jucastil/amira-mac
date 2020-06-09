/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIBASEEXTRACTOR_H
#define  _MIBASEEXTRACTOR_H

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/extractors/MiExtractorCallback.h>

/**
* @DTEXT  Abstract base class for all extractor interfaces.
*
* @ingroup MeshIViz_Extract 
*
* @DESCRIPTION
* All extractor interface classes are derived from this one and
* must implement the setExtractorCallback method.
*/

class MESHIVIZ_API MiBaseExtractor 
{
public:
  virtual ~MiBaseExtractor() {}
  /**
  * Set the user defined extractor callback which will be called before and after each extraction.
  */
  virtual void setExtractorCallback(MiExtractorCallback& extractorCallback) = 0;

};

#endif /* _MIBASEEXTRACTOR_H */


