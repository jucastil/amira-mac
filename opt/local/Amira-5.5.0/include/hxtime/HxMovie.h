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

/// @addtogroup hxtime hxtime
/// @{
#ifndef __AMIRA_HxMovie_H_
#define __AMIRA_HxMovie_H_

#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>

#include "HxTime.h"

/**
   Class to help easy movie generation.
 */
class HxMovie : public HxModule
{
	HX_HEADER(HxMovie); 

public:
	HxPortFilename      	MovieFilename;

	HxPortIntTextN      	Resolution;
	HxPortButtonList    	CreateIt;
	HxPortIntSlider		portFrameNumber;
	HxPortIntTextN      	portFrames;

        /// Video conversion options
        HxPortToggleList        Options;

        HxPortToggleList        ExtraOptions;
	HxPortIntTextN      	ExtrasEvery;
	HxPortIntTextN      	ExtraSize; 

	HxPortMultiMenu		SizeFlags;
	
//	HxPortRadioBox      	SizeFlags, AntiAliasingFlags, FileType;
	HxPortRadioBox      	AntiAliasingFlags, FileType;

	HxPortText      	portTitle; 

	bool	init;
		
	  /// Amira virtual compute function
	void compute();

	  /// Amira virtual update function
	void update();

	const char*frameext() const;

	/// Shall a large .tiff file created for this frame?
	bool CreateLargetiff(int frameno);
	/// Shall a web page be created for this frame?
	bool CreateWebpage(int frameno);

	/// According to the currently selected size, resizes the viewer window
	void autoSize();	

	/// Local movie base class for movie generation
	struct	MovieBase
	{
		/// Called at each frame
		virtual bool shoot(int frame_number) = 0;

		/// Virtual destructor to allow cleanups, mpeg generation, ...
		virtual ~MovieBase() = 0;
	};

private:
	/// The current movie under construction
	MovieBase*myMovie;

	/**
	   Start a movie generation sequence.
	   The start() function is supposed to
	   create a moviebased object. This object
	   is deleted when the movie is finished.
	 */
	virtual MovieBase*start();

public:	/// Constructor
	HxMovie();

protected:
	  // The destructor should be hidden.
	virtual ~HxMovie();

	void info();	
};

#endif /* __AMIRA_HxMovie_H_ */

/// @}
