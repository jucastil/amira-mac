/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SV_MANIP_LIST_
#define  _SV_MANIP_LIST_


// This class helps keep track of 
// selectionPath/manip/xfPath triplets.

class SbPList;
class SoPath;
class SoTransformManip;

// You can add a selectionPath/manip/xfPath triplet to the list.
// Methods let you find the index of this triplet based on any of the three
// things.  You can then use the index to get the selectionPath, manip, or
// xfPath, or remove the triplet from the list.

class IVF_API SvManipList {
 public:
  SvManipList();
  ~SvManipList();
    
  int             getLength() const;

  // append will ref() the paths and the manip
  void            append(SoPath *selectionP, 
                         SoTransformManip *m, SoPath *xfP);
    
  // return the index of the triplet.
  // use this index in calls to:
  // remove(), getSelectionPath(), getManip(), getXfPath()
  int             find(const SoPath *p) const;
  int             find(const SoTransformManip *m) const;
  int             findByXfPath(const SoPath *p) const;
    
  // remove will unref() the paths and the manip
  void            remove(int which);
    
  // these return the paths or the manip.
  SoPath *           getSelectionPath(int which) const;
  SoTransformManip * getManip(int which) const;
  SoPath *           getXfPath(int which) const;
  
 private:
  SbPList *       list;
};

#endif // _SV_MANIP_LIST_
