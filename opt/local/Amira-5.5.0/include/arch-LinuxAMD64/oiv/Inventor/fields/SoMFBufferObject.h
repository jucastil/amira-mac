/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_MFBUFFEROBJECT_H_
#define _SO_MFBUFFEROBJECT_H_

#include <Inventor/devices/SoBufferObject.h>
#include <Inventor/fields/SoSubField.h> 

class INVENTOR_API SoMFBufferObject : public SoMField
{
  // Use standard field stuff
  SO_MFIELD_REQUIRED_HEADER( SoMFBufferObject );
  SO_MFIELD_CONSTRUCTOR_HEADER( SoMFBufferObject );
  SO_MFIELD_VALUE_HEADER( SoMFBufferObject, SoBufferObject*, SoBufferObject* );
  SO_MFIELD_SETVALUESPOINTER_HEADER( SoBufferObject* );

 SoINTERNAL public:

  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal( int index, SoBufferObject *newValue );

  static void initClass();

  static void exitClass();
};

#endif //_SO_MFBUFFEROBJECT_H_
