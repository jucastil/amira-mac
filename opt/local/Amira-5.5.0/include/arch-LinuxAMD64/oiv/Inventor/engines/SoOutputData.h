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



#ifndef  _SO_OUTPUT_DATA_
#define  _SO_OUTPUT_DATA_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

class SoEngine;
class SoFieldContainer;
class SoInput;
class SoOutput;
class SoEngineOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEngineOutputData
//
//  The SoEngineOutputData class holds data about engine outputs: the
//  number of outputs the engine has, the names of the outputs.
//
//  All engines of a given class share the same output data. Therefore,
//  to get information about a particular output in a particular engine
//  instance, it is necessary to pass that instance to the appropriate
//  method.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoEngineOutputData {
 public:
  // Default constructor
  SoEngineOutputData() { }

  SoEngineOutputData(const SoEngineOutputData *);

  // Constructor that takes number of fields as a hint
  SoEngineOutputData(int numOutputs) : outputs(numOutputs)
    { }

  // Destructor
  ~SoEngineOutputData();

  // Adds an output to current data, given name of output,
  // a pointer to field within the engine, and the type of output.
  void                addOutput(const SoEngine *defEngine,
                                const char *outputName,
                                const SoEngineOutput *output,
                                SoType type);

  // Returns number of outputs
  int                 getNumOutputs() const   { return outputs.getLength(); }

  // Returns name of output with given index
  const SbName &      getOutputName(int index) const;

  // Returns pointer to output with given index within given object instance
  SoEngineOutput *    getOutput(const SoEngine *engine,
                                int index) const;

  // Returns index of output, given the output and the engine it
  // is in.
  int                 getIndex(const SoEngine *engine,
                               const SoEngineOutput *output) const;

  // Returns type of output with given index
  const SoType &      getType(int index) const;

  // Methods to read and write the output descriptions
  SbBool              readDescriptions(SoInput *in,
                                       SoEngine *engine) const;
  void                writeDescriptions(SoOutput *out,
                                        SoEngine *engine) const;
 private:
  SbPList             outputs;        // List of outputs (SoOutputEntry)
};    

#endif /* _SO_OUTPUT_DATA_ */
