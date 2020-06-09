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

/// @addtogroup mclib mclib
/// @{
#ifndef __MCLIB_MCMESSAGECOLLECTOR_H__
#define __MCLIB_MCMESSAGECOLLECTOR_H__

#include "McDArray.h"
#include "McString.h"
#include "McWinDLLApi.h"


/** Collects messages in a number of messages slots.
	The number of occurences of each message is counted.
	So one may easily use this to reduce the amount of
	output generated by some classes or modules.

@author Tino Weinkauf
*/
class MCLIB_API McMessageCollector
{
//Friends
//Types
protected:
	///Storage for one message slot and its counter
	struct TCountedMsg
	{
		TCountedMsg()
			:text("")
			,count(0)
		{}

		TCountedMsg(const McString& argText)
			:text(argText)
			,count(0)
		{}

		TCountedMsg(const TCountedMsg& argOther)
			:text(argOther.text)
			,count(argOther.count)
		{}

		virtual ~TCountedMsg(){}

		///Text for the slot
		McString text;
		///Number of times the slot has been called
		int count;
	};


//Construction / Deconstruction
public:
	McMessageCollector();
	virtual ~McMessageCollector();

//Methods
public:
	/** Adds a new slot for a certain type of message.

		@param MessageText
			Text of the message. Will be used, when a report is generated.

		@returns ID of the message slot. Save this for future calls to #countMessage.
	*/
	mclong addMessageSlot(const McString& MessageText);

	/** Use this to increment the counter for a message.

		At the place, where you normally would say
		\verbatim
		printf("Some Message Text");
		\endverbatim
		you simply call this function.

		Later you call #generateReport to print out a summary.

		@param messageSlotID
			ID of the slot to be incremented.
	*/
	void countMessage(const mclong messageSlotID)
	{
		//Safety
		assert( (messageSlotID >= 0) && (messageSlotID < countedMessages.size()) );

		countedMessages[messageSlotID].count++;
	}

	/** Creates summary of messages.

		@param reportText
			This will be filled with the report.
			Already existing content will \b not be deleted.
			So you may easily add some text before the report.

		@param bResetAllSlotCounters
			If true, the counters of all message slots will be reset to zero.

		@returns true, if a report needed to be generated, i.e. #countMessage has been called before.
	*/
	bool generateReport(McString& reportText, const bool bResetAllSlotCounters = true);

	/** Resets the counter of a certain message slot or all slots to zero.

		@param messageSlotID
			ID of the slot to be reset. If you pass -1, then all slots will be reset.
	*/
	void resetSlotCounter(const mclong messageSlotID = -1);

//Attributes
protected:
	///Internal storage of message slots and their counters
	McDArray<TCountedMsg> countedMessages;
};

#endif //__MCLIB_MCMESSAGECOLLECTOR_H__

/// @}