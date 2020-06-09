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

/// @addtogroup hxcore hxcore
/// @{
#ifndef _HXPORTFONTSIZE_H_
#define _HXPORTFONTSIZE_H_

class HxObject;

#include <hxcore/HxPortMultiMenu.h>

/** Provides one combo boxes to choose a font size.
 	Available font size are the ones which can be displayed. 
	Not displayable font size are hidden.
*/
class HXCORE_API HxPortFontSize: public HxPortMultiMenu {

	MC_ABSTRACT_HEADER(HxPortFontSize);

protected :

	///
	McDArray<int>	m_fontSizeList;

	///
	int				m_fontIncrement;

	/// Build the list of available font size
	McDArray<int> buildAvailableFontSizeList(int min, int max);

public :

	HxPortFontSize(HxObject *object, const char *name);
	virtual ~HxPortFontSize();

	/// Set the font size range.
	virtual void setMinMax(int min, int max);

	virtual int getMinValue() const;
	virtual int getMaxValue() const;

	/// Set the increment when building the font size list.
	virtual void setIncrement(int theIncrement);

	/// Returns current increment used to build font size list
	virtual int getIncrement();

	/** Set the current font size.
	 *  If fontSize is not available, the previous (in size) 
	 *  available font size is selected.
	 */
	virtual void setValue(int fontSize);

	/// Returns current font size item
	virtual int getValue();

	/// Command interface.
	virtual int parse(Tcl_Interp* t, int argc, char **argv);

	/// Save state method.
	virtual void saveState(FILE* fp);

	/// Returns current state in ascii string.
	virtual void getState(McString& state);

	/// Restores current state from ascii string.
	virtual int setState(const McString& state);
};

#endif /* _HXPORTFONTSIZE_H_ */

/// @}
