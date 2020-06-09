/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Apr 2003)
**=======================================================================*/
#ifndef  _SO_DIALOG_WIDGET_LIST_
#define  _SO_DIALOG_WIDGET_LIST_

#include <Inventor/SbPList.h>
#include <Inventor/Xt/SoXt.h>

class DIALOGVIZ_API SoDialogWidgetList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoDialogWidgetList();
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoDialogWidgetList(int size);
  /**
   * Constructor that copies the contents of another list.
   */
  SoDialogWidgetList(const SoDialogWidgetList &l);
  /**
   * Destructor.
   */
  ~SoDialogWidgetList();

  /**
   * Adds a pointer to the end of the list.
   */
  void append(SoWidget ptr);

  /**
   * Inserts given pointer in list before pointer with given index.
   */
  void insert(SoWidget ptr, int addBefore);

  /**
   * Returns index of given widget in list, or -1 if not found.
   */
  int find(const SoWidget ptr) const;

  /**
   * Copies a list.
   */
  SoDialogWidgetList & operator = (const SoDialogWidgetList &l);

  /**
   * Accesses an element of a list.
   */
  SoWidget& operator [](int i) const;

  /**
   * Sets an element of a list.
   */
  void set(int i, SoWidget& ptr);
};

#endif // _SO_DIALOG_WIDGET_LIST_
