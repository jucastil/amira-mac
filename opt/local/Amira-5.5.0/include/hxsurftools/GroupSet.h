/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef GROUP_SET_H
#define GROUP_SET_H

#include <mclib/McIteratorInterface.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McString.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

class HxSelectInterface;

//Data:
struct Group {
  McString name;
  McBitfield bits;
};



/// GroupSet, a wrapper to use trianglegroups
class HXSURFTOOLS_API GroupSet{

 public:

  ///constructor
  GroupSet( HxSelectInterface& );

  ///destructor
  ~GroupSet();

  /// returns an iterator of the group-set
  McIterator * iterator(){ return new GroupIterator(this); }

  /// appends group
  void add( Group& );
  
  /// removes group
  /// NOTE: Do not use with Iterator at the same time
  bool remove(const McString &name );  

  /// returns Group with the name name 
  Group* get(const McString &name );

  /// returns the size of set
  int length() { return groups.size(); }

  /// updates the groupdata if HxSelectInterface changed
  void update();

  /// updates a singledata group
  void update( Group &g );

  /// stores groupdata explicitly in selectioninterface
  void storeGroups();

private:

  ///copies groupdata to the groupfield
  void initGroups();
  
  /// owner of the groupset
  HxSelectInterface* owner;

  McDArray<Group> groups;


  ////////////////////////////////////////////////
  // implementation of Iterator - interface
  class GroupIterator : public McIterator {
      
  private:
      
      GroupSet* parent;
      int position;
      
  public:
      
      //constructor
      GroupIterator(GroupSet* parent){
          this->parent = parent;
          position=0;
      }
      bool hasNext(){ 
          return ( position < parent->groups.size() );
      }
      void* next(){ 
          if( position >= parent->groups.size() ) return NULL;
          return &( parent->groups[ position++ ] );
      }
      bool remove(){
          if( (position < 1) || (position > parent->groups.size()) ) 
              return false;
          if( parent->remove( parent->groups[position-1].name ) ) {
              position--;
              return true;
          }
          return false;
      }
  };

  friend class GroupIterator;

};

#endif

/// @}
