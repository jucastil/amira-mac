/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLINTERPOUTPUT_DATA_
#define  _SO_VRMLINTERPOUTPUT_DATA_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

class SoVRMLInterpolator;
class SoFieldContainer;
class SoInput;
class SoOutput;
class SoVRMLInterpOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLInterpOutputData
//
//  The SoVRMLInterpOutputData class holds data about VRMLInterpolator 
//  outputs: the number of outputs the VRMLInterpolator has, 
//  the names of the outputs.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLInterpOutputData {
 public:
  // Default constructor
  SoVRMLInterpOutputData() { }

  SoVRMLInterpOutputData(const SoVRMLInterpOutputData *);

  // Constructor that takes number of fields as a hint
  SoVRMLInterpOutputData(int numOutputs) : outputs(numOutputs)
    { }

  // Destructor
  ~SoVRMLInterpOutputData();

  // Adds an output to current data, given name of output,
  // a pointer to field within the VRMLInterpolator, and the type of output.
  void                addOutput(const SoVRMLInterpolator *defVRMLInterp,
                                const char *outputName,
                                const SoVRMLInterpOutput *output,
                                SoType type);

  // Returns number of outputs
  int                 getNumOutputs() const   { return outputs.getLength(); }

  // Returns name of output with given index
  const SbName &      getOutputName(int index) const;

  // Returns pointer to output with given index within given object instance
  SoVRMLInterpOutput *        getOutput(const SoVRMLInterpolator *VRMLInterp,
                                        int index) const;

  // Returns index of output, given the output and the VRMLInterpolator it
  // is in.
  int                 getIndex(const SoVRMLInterpolator *VRMLInterp,
                               const SoVRMLInterpOutput *output) const;

  // Returns type of output with given index
  const SoType &      getType(int index) const;

  // Methods to read and write the output descriptions
  SbBool              readDescriptions(SoInput *in,
                                       SoVRMLInterpolator *VRMLInterp) const;
  void                writeDescriptions(SoOutput *out,
                                        SoVRMLInterpolator *VRMLInterp) const;
 private:
  SbPList             outputs;        // List of outputs (SoOutputEntry)
};    

#endif /* _SO_VRMLINTERPOUTPUT_DATA_ */
