/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_BASE_
#define  _PB_BASE_

#include <Inventor/SbBasic.h>
#include <MeshViz/PbBasic.h>

class PoBase;

/**
 * @DTEXT  Abstract class for all basic objects.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    Abstract class for all basic objects. This class handles a connection mechanism 
 *    with PoBase objects. Each instance of this class maintains a list of PoBase 
 *    objects. So when an instance of this class is modified, the list of PoBase objects is 
 *    informed of this change, and thus, they can update themselves. For more 
 *    information about the connection mechanism, see the section "Connection 
 *    mechanism" of the paragraph "What you must know" of the reference manual.
 *    The constructor per copy and the assignment operator of any Pbxxx object do not 
 *    copy the reference to Poxxx objects. This restriction prevents several Pbxxx objects 
 *    (of the same class) from referencing the same Poxxx object.
 * 
 */
class MESHVIZ_API PbBase {

 public:

  /**
   * Activates/deactivates the mechanism of connection. If the mechanism is 
   * deactivated, the list of connected objects does not change, but the connected 
   * objects are not informed of any change.
   */
  void enableConnection(SbBool flag) 
    { m_connectionEnabled = flag; } 

  /**
   * Returns TRUE if the connection mechanism is active, otherwise FALSE.
   */
  SbBool isConnectionEnabled() const
    { return m_connectionEnabled; }

  /**
   * Simulates the changing of an instance of this object, so all connected objects 
   * are informed of this change.
   */
  void touch();

  /**
   * Assignment operator.
   */
  PbBase &operator=(const PbBase &base);

  /*--------------------------------------------------------------------------*/
 PoINTERNAL public:
  // Add or remove a PoBase object to the list of connected objects
  void addConnection(const PoBase *baseObj);
  SbBool removeConnection(const PoBase *baseObj);
  
  // Change type for a PbBase Object
  enum ChangeType {
    TGS_TOUCH_TYPE,
    TGS_DELETE_TYPE,
    TGS_GEOMETRY_TYPE,
    TGS_SET_OF_VALUES_TYPE,
    TGS_SET_OF_STRINGS_TYPE,
    TGS_SET_OF_VECTORS_TYPE,
    TGS_DOMAIN_TRANSFORM_TYPE
  };
  
  // Get changement type
  ChangeType getChangeType() const { return m_changeType; }
  void getDataChange(int &data) const { data = m_intDataChange; }

 protected:
  // Constructors & destructors
  PbBase();
  PbBase(const PbBase &base);
  virtual ~PbBase();
  
  // Empty the list of connected objects
  void removeAllConnection();
  
  // Set changement type and data for a PbBase Object
  void setChangeType(ChangeType type) { m_changeType = type; }
  void setDataChange(int data) { m_intDataChange = data; }
  
  // Notify a change to all connected objects 
  void notifyChange();
  
 private:
  struct Element {
    PoBase *baseObj;
    Element *next;
  };
  
  // Used by constructor per copy and affectation operator
  void copy(const PbBase &base, SbBool isConstructorPerCopy);
  
  // Header of the list of PoBase object
  Element *m_headBaseObjList;
  
  // Indicate if the connection is enabled or not
  SbBool m_connectionEnabled;
  
  // Type of change
  ChangeType m_changeType;
  
  // Integer data change
  int m_intDataChange;
}; 
/*---------------------------------------------------------------------------*/

#endif /* _PB_BASE_ */

