/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ENGINE_
#define  _SO_ENGINE_

#include <Inventor/SbBasic.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/SoLists.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEngine
//
//  Base SoEngine class (abstract).
//
//////////////////////////////////////////////////////////////////////////////


class SoFieldData;
class SoEngineList;
class SoEngineOutput;
class SoEngineOutputList;
class SoEngineOutputData;
class SoField;
class SoOutput;
class SoInput;

/**
 * Base class for all engines.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   SoEngine is the abstract base class for all engines. Engines are objects used
 *   for animation and behavior. They are lightweight objects that are connected
 *   between nodes, the clock, and other engines to form interesting behaviorial
 *   objects (e.g., a spinning windmill).
 *   
 *   Engines are used to animate parts of a scene and/or to constrain one part of a
 *   scene in relation to some other part of the scene. An engine receives a number
 *   of input values, performs some operation on them, and then copies the results
 *   into one or more output fields. Both the inputs and the outputs can be connected
 *   to other fields or engines in the scene graph. When an engine's output values
 *   change, those new values are sent to any fields or engines connected to them.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoBoolOperation,
 *    SoCalculator,
 *    SoComposeMatrix,
 *    SoComposeRotation,
 *    SoComposeRotationFromTo,
 *    SoComposeVec2f,
 *    SoComposeVec2i32,
 *    SoComposeVec2s,
 *    SoComposeVec3f,
 *    SoComposeVec4f,
 *    SoComputeBoundingBox,
 *    SoConcatenate,
 *    SoCounter,
 *    SoDecomposeMatrix,
 *    SoDecomposeRotation,
 *    SoDecomposeVec2f,
 *    SoDecomposeVec2i32,
 *    SoDecomposeVec2s,
 *    SoDecomposeVec3f,
 *    SoDecomposeVec4f,
 *    SoElapsedTime,
 *    SoGate,
 *    SoInterpolate,
 *    SoOnOff,
 *    SoOneShot,
 *    SoSelectOne,
 *    SoTimeCounter,
 *    SoTransformVec3f,
 *    SoTriggerAny
 * 
 * 
 */ 

class INVENTOR_API SoEngine : public SoFieldContainer {

 public:

  /**
   * Returns the type identifier for the SoEngine class.
   */
  static SoType       getClassTypeId();

  /**
   * Returns a list of outputs in this engine. Use getOutputName() to get the
   * names of the outputs, and use SoEngineOutput::getConnectionType() to
   * determine their types.
   */
  virtual int         getOutputs(SoEngineOutputList &list) const;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the engine output with the given name. If no such output
  * exists, NULL is returned.
  */

#else
  /**
  * Returns a pointer to the engine output with the given name. If no such output
  * exists, NULL is returned.
  */

#endif //OIV_NET_DOC
  SoEngineOutput *    getOutput(const SbName &outputName) const;

  /**
   * Returns (in outputName) the name of the engine output (output). Returns FALSE if
   * the engine output is not contained within the engine instance.
   */
  SbBool              getOutputName(const SoEngineOutput *output,
                                    SbName &outputName) const;

  /**
   * Creates and returns an exact copy of the engine. All connections to inputs are
   * copied as is (without copying what's at the other end).
   */
  SoEngine *          copy() const;

  /**
   * Looks up engine(s) by name.
   */
  static SoEngine *   getByName(const SbName &name);
  /**
   * Looks up engine(s) by name.
   */
  static int          getByName(const SbName &name, SoEngineList &list);

 protected:

  // User-written evaluation engine.
  virtual void        evaluate() = 0;

 SoINTERNAL public:

  // wrapper for the user's evaluate() engine
  void                evaluateWrapper();

  // Propagates modification notification through an instance.
  virtual void        notify(SoNotList *list);

  // Initializes base engine class
  static void         initClass();
  static void         exitClass();

  // Info on outputs:
  virtual const SoEngineOutputData *getOutputData() const = 0;

  // Initialize ALL Inventor engine classes
  static void         initClasses();
  static void         exitClasses();

  // Writes instance to SoOutput. (Used only for last stage of writing)
  virtual void        writeInstance(SoOutput *out);

  // Copies an instance that is encountered through a field connection
  virtual SoFieldContainer *  copyThroughConnection() const;

  // Recursive procedure that determines if this engine should be
  // copied during a copy operation, or just referenced as is
  SbBool              shouldCopy() const;

  // A very annoying double notification occurs with engines
  // that enable their outputs during inputChanged; this flag
  // prevents that:
  SbBool              isNotifying() const { return notifying; }

 protected:

  // Constructor, destructor
  SoEngine();
  virtual ~SoEngine();

  // Reads stuff into instance. Returns FALSE on error
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  // This is called whenever the value of an input is changed. The
  // default method does nothing. Subclasses can override this to
  // detect when a specific field is changed.
  virtual void        inputChanged(SoField *whichField);

  // This is used by the input&output inheritence mechanism, hidden in
  // the SoSubEngine macros
  static const SoFieldData            **getInputDataPtr()  { return NULL; }
  static const SoEngineOutputData     **getOutputDataPtr() { return NULL; }

  // Write output type information for engines that are not built-in.
  void                writeOutputTypes(SoOutput *out);

 private:

  static SoType classTypeId;
  SbBool needsEvaluation;        // Dirty bit
  SbBool notifying;
  friend class SoEngineOutput;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEngineOutput
//
//  Engine outputs.  They are lists of fields to be written into,
//  and a pointer back to the containing engine.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Class for all engine outputs.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   SoEngineOuput is the class for all engine output fields. There is no public
 *   constructor routine for this class. Only the engine classes create instances of
 *   SoEngineOutput.
 *   
 *   Each engine creates one or more engine outputs. The type of the output is
 *   documented in the engine reference pages. There is also an SoEngineOutput method
 *   for querying the connection type.
 *   
 *   The application can at any time enable or disable the engine outputs. By default
 *   the engine outputs are enabled.
 * 
 * @SEE_ALSO
 *    SoEngine
 * 
 * 
 */ 

class INVENTOR_API SoEngineOutput {

 public:
  /**
   * Returns the type of field this output can connect to.
   */
  SoType              getConnectionType() const;

#ifdef OIV_NET_DOC
  /**
  * Returns the number of fields this output is writing to, and adds references to
  * those fields to the given list.
  */

#else
  /**
  * Returns the number of fields this output is writing to, and adds pointers to
  * those fields to the given list.
  */

#endif //OIV_NET_DOC
  int                 getForwardConnections(SoFieldList &list) const;

  /**
   * Enables or disables all connections from this output. If the connections are
   * disabled, values will not be output along them. By default, outputs are enabled.
   */
  void                enable(SbBool flag);
  /**
   * Returns TRUE if this output is currently enabled.
   */
  SbBool              isEnabled() const       { return enabled; }

  /**
   * Returns containing engine.
   */
  SoEngine *          getContainer() const            { return container; }

 SoINTERNAL public:
  SoEngineOutput();

  virtual ~SoEngineOutput();

  void                setContainer(SoEngine *eng)     { container = eng; }

  // Adds/removes connection to field
  void                addConnection(SoField *);
  void                removeConnection(SoField *);

  // Number of connections this output currently has
  int                 getNumConnections() const
    { return connections.getLength(); }

  // Returns the fields this output is writing into
  SoField *           operator[](int i) const
    { return connections.get(i); }

  // Before evaluating (which is done with the regular field API),
  // we must disable notification on all the fields we're about to
  // write into.  After evaluating, the bits are restored:
  void                prepareToWrite() const;
  void                doneWriting() const;

 private:
  SbBool              enabled;
  SoFieldList         connections;
  SoEngine            *container;
};

#endif /* _SO_ENGINE_ */



