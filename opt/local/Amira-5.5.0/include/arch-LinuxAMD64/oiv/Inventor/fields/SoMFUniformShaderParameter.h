/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_MF_UNIFORM_SHADER_PARAMETER_
#define  _SO_MF_UNIFORM_SHADER_PARAMETER_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/nodes/SoShaderParameter.h>

#ifdef OIV_NET_DOC
/**
*
* @VSGEXT
*   Multiple-value field containing any number of references to SoUniformShaderParameter nodes.
*
* @ingroup fields
*
* @DESCRIPTION
*   This field maintains a set of references to SoUniformShaderParameter instances, correctly
*   maintaining their reference counts.
*
*   An SoMFUniformShaderParameter is written to file as one or more SoUniformShaderParameters.
*   When more than one value is
*   present, all of the values are enclosed in square brackets and separated by
*   commas. For example:
*
*   <PRE>
*    [ ShaderParameter1f {
*        name "shininess"
*        value 20
*      },
*
*      ShaderParameter3f {
*        name "eyePosition"
*        value 0 0 0
*      }
*    ]
*    </PRE>
*
*
*
*/
#else
/**
*
* @VSGEXT
*   Multiple-value field containing any number of pointers to SoUniformShaderParameter nodes.
*
* @ingroup fields
*
* @DESCRIPTION
*   This field maintains a set of pointers to SoUniformShaderParameter instances, correctly
*   maintaining their reference counts.
*
*   An SoMFUniformShaderParameter is written to file as one or more SoUniformShaderParameters.
*   When more than one value is
*   present, all of the values are enclosed in square brackets and separated by
*   commas. For example:
*
*   <PRE>
*    [ ShaderParameter1f {
*        name "shininess"
*        value 20
*      },
*
*      ShaderParameter3f {
*        name "eyePosition"
*        value 0 0 0
*      }
*    ]
*    </PRE>
*
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoMFUniformShaderParameter : public SoMField {

  SO_MFIELD_REQUIRED_HEADER(SoMFUniformShaderParameter);
  SO_MFIELD_CONSTRUCTOR_HEADER(SoMFUniformShaderParameter);
  SO_MFIELD_VALUE_HEADER(SoMFUniformShaderParameter, SoUniformShaderParameter *, SoUniformShaderParameter *);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SoUniformShaderParameter *);

  /**
   * Adds a uniform shader parameter as last one in group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void addShaderParameter(SoUniformShaderParameter *shaderParameter);

  /**
   * Adds a uniform shader parameter so that it becomes the one with the given index.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void insertShaderParameter(SoUniformShaderParameter *shaderParameter, int newUniformShaderParameterIndex);

#ifdef OIV_NET_DOC
  /**
  * Returns reference to n'th uniform shader parameter node.
  */

#else
  /**
  * Returns pointer to n'th uniform shader parameter node.
  */

#endif //OIV_NET_DOC
  SoUniformShaderParameter *getShaderParameter(int index) const;

  /**
   * Finds index of given uniform shader parameter within group.
   */
  int findShaderParameter(const SoUniformShaderParameter *shaderParameter) const;

  /**
   * Find the first parameter with the given name. Return NULL if not found.
   */
  SoUniformShaderParameter* findUniformParameterByName(const SbString& name);

  /**
   * Returns number of uniform shader parameters.
   */
  int getNumShaderParameters() const;

  /**
   * Removes uniform shader parameter with given index from group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeShaderParameter(int index);

  /**
   * Removes first instance of given uniform shader parameter from group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeShaderParameter(SoUniformShaderParameter *shaderParameter)
  { removeShaderParameter(findShaderParameter(shaderParameter)); }

  /**
   * Removes first instance of given uniform shader parameter with given name from group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeShaderParameter(const SbString& name);

  /**
   * Removes all uniform shader parameters from group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeAllShaderParameters();

  /**
   * Replaces uniform shader parameter with given index with new uniform shader parameter.
   */
  void replaceShaderParameter(int index, SoUniformShaderParameter *newUniformShaderParameter);

  /**
   * Replaces first instance of given uniform shader parameter with new uniform shader parameter
   */
  void replaceShaderParameter(SoUniformShaderParameter *oldUniformShaderParameter,
                              SoUniformShaderParameter *newUniformShaderParameter)
  { replaceShaderParameter(findShaderParameter(oldUniformShaderParameter), newUniformShaderParameter); }

  /**
   * Returns a pointer to the internally maintained array that can be modified.
   * The values in the array may be changed, but values cannot be added or removed. It is illegal to call any other
   * editing methods between startEditing() and finishEditing() (e.g. set1Value(), setValue(), etc.).
   *
   * Fields, engines or sensors connected to this field and sensors are not notified that this field has changed until
   * finishEditing() is called. Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines
   * and sensors that the field changed, even if none of the values actually were changed.
   * [OIVNET-WRAPPER-RETURN-TYPE ARRAY{GetNum()}]
   */
  SoUniformShaderParameter** startEditing();

  /** Indicates that batch edits have finished. @see startEditing(). */
  void finishEditing();

  SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Update a copied field to use the copy of each uniform shader parameter if there is one
  virtual void fixCopy(SbBool copyConnections);

  // Override this to also check the stored uniform shader parameters
  virtual SbBool referencesCopy() const;

private:
  // Override this to maintain write-references in uniform shader parameters
  virtual void countWriteRefs(SoOutput *out) const;

  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal(int index, SoUniformShaderParameter *newValue);

  /**
   * Return true if param has the given name
   */
  static bool hasGivenName(SbString name, const SoShaderParameter* param);

  SoUniformShaderParameter** m_oldValues;
  int m_oldNum;
};

#endif /* _SO_MF_UNIFORM_SHADER_PARAMETER_ */

