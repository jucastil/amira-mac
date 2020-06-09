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


#ifndef  _SO_VRMLINTERP_
#define  _SO_VRMLINTERP_

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/VRMLnodes/SoVRMLSubInterpolator.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLInterpolator
//
//  Base SoVRMLInterpolator class (abstract).
//
//////////////////////////////////////////////////////////////////////////////


class SoFieldData;
class SoVRMLInterpList;
class SoVRMLInterpOutput;
class SoVRMLInterpOutputList;
class SoVRMLInterpOutputData;
class SoField;
class SoOutput;
class SoInput;

/**
 * @VSGEXT Abstract base class for VRML interpolators.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   SoVRMLInterpolator is the abstract base class for all VRML interpolators.
 * 
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 *
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 *
 * @SEE_ALSO
 *    SoVRMLColorInterpolator,
 *    SoVRMLCoordinateInterpolator,
 *    SoVRMLNormalInterpolator,
 *    SoVRMLOrientationInterpolator,
 *    SoVRMLPositionInterpolator,
 *    SoVRMLScalarInterpolator,
 *    SoVRMLTimeSensor
 * 
 * 
 */ 

class INVENTOR_API SoVRMLInterpolator : public SoVRMLNode {

  SO_NODE_ABSTRACT_HEADER(SoVRMLInterpolator);

 public:


  /**
   * Returns a list of outputs in this VRML interpolator. This is virtual so that
   * private outputs can be hidden. Use getOutputName() to get the names of
   * the fields, and use @B getConnectionType @b() to figure out their types.
   * Returns the number of outputs added to the list.
   */
  virtual int         getOutputs(SoVRMLInterpOutputList &list) const;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the VRML interpolator output with the given name. If no
  * such output exists, NULL is returned.
  */

#else
  /**
  * Returns a pointer to the VRML interpolator output with the given name. If no
  * such output exists, NULL is returned.
  */

#endif //OIV_NET_DOC
  SoVRMLInterpOutput *        getOutput(const SbName &outputName) const;

#ifdef OIV_NET_DOC
  /**
  * Returns (in @B outputName @b) the name of the referenced output. Returns false
  * if the output is not contained within the VRML interpolator instance. 
  */

#else
  /**
  * Returns (in @B outputName @b) the name of the output pointed to. Returns FALSE
  * if the output is not contained within the VRML interpolator instance. 
  */

#endif //OIV_NET_DOC
  SbBool              getOutputName(const SoVRMLInterpOutput *output,
                                    SbName &outputName) const;

  /**
   * Wrapper for the user's evaluate() interpolator.
   */
  void                evaluateWrapper(SoVRMLInterpOutput *interp);

  /**
   * Creates and returns a copy of the VRML interpolator. All connections to inputs
   * are copied as is (without copying what's at the other end).
   */
  SoVRMLInterpolator *                copy() const;

  /**
   * A VRML interpolator can be given a name using @B setName @b() (which is a
   * method on SoBase). This method allows VRML interpolators to be
   * looked up by name.
   * It returns the last VRML interpolator with the specified name.
   */
  static SoVRMLInterpolator * getByName(const SbName &name);
#ifdef OIV_NET_DOC
  /**
  * A VRML interpolator can be given a name using @B setName @b() (which is a
  * method on SoBase). This method allows VRML interpolators to be 
  * looked up by name.
  * It returns the number of VRML interpolators with
  * the specified name,
  * and adds to list references to those interpolators.
  */

#else
  /**
  * A VRML interpolator can be given a name using @B setName @b() (which is a
  * method on SoBase). This method allows VRML interpolators to be 
  * looked up by name.
  * It returns the number of VRML interpolators with
  * the specified name,
  * and adds to list pointers to those interpolators.
  */

#endif //OIV_NET_DOC
  static int          getByName(const SbName &name, SoVRMLInterpList &list);


 SoINTERNAL public:

  virtual const SoVRMLInterpOutputData *      getOutputData() const = 0; 

  // Propagates modification notification through an instance.
  virtual void        notify(SoNotList *list);

  // Initializes base engine class
  static void         initClass();
  static void         exitClass();

  // Initialize ALL Inventor engine classes
  static void         initClasses();
  static void         exitClasses();

  // Writes instance to SoOutput. (Used only for last stage of writing)
  //virtual void      writeInstance(SoOutput *out);

  // Copies an instance that is encountered through a field connection
  virtual SoFieldContainer *  copyThroughConnection() const;

  // Recursive procedure that determines if this engine should be
  // copied during a copy operation, or just referenced as is
  SbBool              shouldCopy() const;

  // A very annoying double notification occurs with engines
  // that enable their outputs during inputChanged; this flag
  // prevents that:
  SbBool              isNotifying() const { return notifying; }
  SbBool              needsEvaluation;        // Dirty bit
  SbBool              notifying;

 protected:

  // User-written evaluation engine.
  virtual void        evaluate(SoVRMLInterpOutput *interp) = 0;
  static const SoFieldData            **getInputDataPtr();
  static const SoVRMLInterpOutputData    **getOutputDataPtr();

  // Constructor, destructor
  SoVRMLInterpolator();
  virtual ~SoVRMLInterpolator();

  // Reads stuff into instance. Returns FALSE on error
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  // This is called whenever the value of an input is changed. The
  // default method does nothing. Subclasses can override this to
  // detect when a specific field is changed.
  virtual void        inputChanged(SoField *whichField);

  // Write output type information for engines that are not built-in.
  void                writeOutputTypes(SoOutput *out);

 private:
  static SoFieldData *inputData; 
  static SoVRMLInterpOutputData *outputData;
  static const SoFieldData **parentInputData;  
  static const SoVRMLInterpOutputData **parentOutputData;
  
  friend class SoVRMLInterpOutput;

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLInterpOutput
//
//  Engine outputs.  They are lists of fields to be written into,
//  and a pointer back to the containing engine.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Class for all VRML interpolator outputs.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   SoVRMLInterpOutput is the class for all VRML interpolator output fields. There
 *   is no public constructor routine for this class. Only the VRML interpolator
 *   classes create instances of SoVRMLInterpOutput.
 *   
 *   Each VRML interpolator creates one or more VRML interpolator outputs. The type of
 *   the output is documented in the VRML interpolator reference pages. There is also
 *   an SoVRMLInterpOutput method for querying the connection type.
 *   
 *   The application can at any time enable or disable the VRML interpolator outputs.
 *   By default the VRML interpolator outputs are enabled.
 * 
 * @SEE_ALSO
 *    SoVRMLInterpolator
 * 
 * 
 */ 

class INVENTOR_API SoVRMLInterpOutput {

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
   * Returns containing VRML interpolator.
   */
  SoVRMLInterpolator *        getContainer() const    { return container; }

 SoINTERNAL public:
  SoVRMLInterpOutput();

  virtual ~SoVRMLInterpOutput();

  SbBool          read(SoInput *in, const SbName &outName,
                       SoFieldContainer *object );
  void        setContainer(SoVRMLInterpolator *eng)   { container = eng; }

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
  SoVRMLInterpolator          *container;
  SbBool              needsEvaluation;        // Dirty bit
};

#endif /* _SO_VRMLINTERP_ */
