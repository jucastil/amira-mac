/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FIELD_CONVERTER_
#define  _SO_FIELD_CONVERTER_

#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFieldConverter
//
//  Abstract base class for all field converter engines. A field
//  converter engine is used to convert the value of a field of one
//  type to another. These engines are registered with the global
//  database so connections between fields of different types can be
//  made by automatically inserting a converter instance.
//  A single class of converter engine may be registered for several
//  different conversions.
//  Field converters are never written to file
//  (SoField::writeConnection takes care of that).
//
//////////////////////////////////////////////////////////////////////////////


SoEXTENDER class INVENTOR_API SoFieldConverter : public SoEngine {

  SO_ENGINE_ABSTRACT_HEADER(SoFieldConverter);

 public:
  // These must be defined in each subclass. They return the input
  // and output connections of the given types.
  virtual SoField *           getInput(SoType type)  = 0;
  virtual SoEngineOutput *    getOutput(SoType type) = 0;

  // Returns the input that is connected.  By default, this searches
  // through the field data for the field that is connected;
  // you can redefine to make more efficient.
  virtual SoField *           getConnectedInput();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  static void         initClasses();  // init all builtin converters
  static void         exitClasses();

  // Adds all fields connected from the output of the converter to
  // the given list
  int                 getForwardConnections(SoFieldList &list) const;

 protected:
  SoFieldConverter();

  virtual ~SoFieldConverter();
};

#endif /* _SO_FIELD_CONVERTER_ */
