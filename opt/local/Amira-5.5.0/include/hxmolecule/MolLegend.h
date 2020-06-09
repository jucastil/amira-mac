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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef MOL_LEGEND_H
#define MOL_LEGEND_H

#include <mclib/McDArray.h>
#include <mclib/McHandable.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#else
#include <iostream.h>
#endif

#include <qobject.h>
#include <qurl.h>
#include <mclib/McString.h>
#include <Inventor/SbColor.h>
class HxMolecule;
class McVec2f;
class MtGroupRef;
class QTextBrowser;

/** MolLegend displays a HTML table containing groups
    and attributes and their corresponding colors in a
    HxHTML window.
    The groups and colors must be set with one of the update()
    methods.
    With linkUse set a callback will be used which enables
    selection of groups by clicking on the table entries
**/

class MolLegend : public QObject , public McHandable
{
    Q_OBJECT
public:
    
    /** constructor will create a HxHTML to show the legend **/ 
    MolLegend();
    
    /** destructor **/
    ~MolLegend();
    
    /** activates or deactivtes linkUse 
        linkUse will enable the user to click on groups in the
        legend which results in selecting them. linkUse can be
        only used if one of the update methods which have
        the HxMolecule as calling paramteter is used, 
        if not it will be automatically disabled **/
    void setLinkUse(bool linkUse);
    
    /** shows the MolLegend window **/
    void show();
    
    /** returns whether MolLegend window is currently shown **/
    bool isVisible();

    /** ------ update methods
        following methods will update the legend with entries as 
        specified by the calling parameters,
        each method requires a list of colors @c cl which corresponds
        to and has to be equal in size to the groups given in the
        other parameters which define the groups to be displayed **/
    
    /** shows legend containing the names of the entries in the 
        GroupingLevel level **/
    void update(
        HxMolecule* m,
        int levelIx,
        const McDArray<SbColor>& cl);
    
    /** shows legend containing the entries of the 
        GroupingAttribute @c attrIx of level @c levelIx **/ 
    void update(
        HxMolecule* m,
        int levelIx,
        int attrIx,
        const McDArray<SbColor>& cl);
   
    /** shows legend containing the entries of the GroupRef 
        list @c refList **/
    void update(
        HxMolecule* m,
        const McDArray<MtGroupRef>& refList,
        const McDArray<SbColor>& colList);

    /** show legend by giving names directly - 
        linkUse will be deactivated automatically
        only to be used in special situations and 
        when linkUse is not necessary **/
    void update(
        const McDArray<McString>& nList,
        const McDArray<SbColor>& colList);


private:

    /** determines whether entries in Legend will be shown
        as links to enable linkClicked selection **/
    bool linkUse;
    
    /// basis Molecule - must be set when linkUse is true
    HxMolecule* hxMol;

    /// HxHTML browser in which the legend is displayed as HTML code
    QTextBrowser* browser;
    
    /** updates the legend with the entries @c nlist,@c linksNameList
        which are of the colors @c colList **/
    void updateTable(
        const McDArray<McString>& nList,
        const McDArray<McString>& linkNameList,
        const McDArray<SbColor>& colList);

    /** -- methods for generating the HTML code from a list of
        entries @c nameList with linkNames @c linkNameList and
        colors @c colList. The resulting string will be written
        to @c result. Pagenumber can be optionally given to
        show a definite page (if there are so many entries
        that several pages are used). PageNumber should only
        be set by the function pageLinkClicked 
        returns the optimal size of the browser as Vector **/
    McVec2f getHTML(
        McString& result,
        const McDArray<McString>& nameList,
        const McDArray<McString>& linkNameList,
        const McDArray<SbColor>& colList,
        int pageNumber=0);
    
    /** prints color @c color in HTML format to stream @c ofs **/
    void printColor(
        ostream& ofs, 
        const SbColor* color);

    /** prints table entry @c name,@c linkname with color @c color
        to stream @c ofs **/
    void printTableEntry(
        ostream& ofs,
        const SbColor* color, 
        const char* name, 
        const char* linkName);

    /** function is used by the linkClickedClicked callback to select
        display the page @c pagenumber **/
    void pageLinkClicked(int pageNumber);

    /** function is used by the linkClicked callback to select
        all groups of level @c levelIx whose attribute @c attrIx
        has the element value of element @c elementIx **/
    void attributeLinkClicked(int levelIx, int attrIx, int elementIx);

    /** lists for storing the update information, need to be set
        when the pageUse callback is used **/
    McDArray<McString> nameList;
    McDArray<McString> linkNameList;
    McDArray<SbColor> colorList;
protected slots:
    void anchorClicked(const QUrl& str);
};
#endif

/// @}
