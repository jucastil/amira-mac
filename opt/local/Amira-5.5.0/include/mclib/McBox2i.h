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
#ifndef MC_BOX2I_H
#define MC_BOX2I_H

#include "McVec2i.h"
#include "McWinDLLApi.h"

/// This class represents a 2D box, i.e. a rectangle
class McBox2i {
  public:

    /// Default constructor - leaves box totally empty
    McBox2i()	{ makeEmpty(); }

    /// Constructor with one point, make box contain exactly one  point
    McBox2i(const McVec2i& p) : p1(p), p2(p)	{ }

    //// Constructor given bounds
    McBox2i(int xmin, int xmax, int ymin, int ymax)
	: p1(xmin, ymin), p2(xmax, ymax) { }

    // // Constructor given minimum and maximum points
      //McBox2i(const McVec2i &_min, const McVec2i &_max)
    //{ p1 = _min; p2 = _max; }

    /// Assignment.
    McBox2i& operator=(const McBox2i& o) {
	p1=o.p1; p2=o.p2; return *this;
    }

    /// Set box by origin and size
    void setOriginAndSize(const McVec2i& o, const McVec2i& s) {
      p1 = o;
      p2.x = p1.x + s.x-1 ;
      p2.y = p1.y + s.y-1 ;
    }

    /// Set rect by lower left and width and height
    void setRect(int x,int y, int w, int h) {
	p1.x = x;
	p1.y = y;
	p2.x = x + w-1;
	p2.y = y + h-1;
    }

    /// Set size (width, height).
    void setSize(int x,int y) {
	p2.x = p1.x+x-1;
	p2.y = p1.y+y-1;
    }

    /// Set Width.
    void setWidth(int w) {
	p2.x = p1.x+w-1;
    }
    /// Set height.
    void setHeight(int h) {
	p2.y = p1.y+h-1;
    }

    /// Same as setCorners().
    void setBounds(const McVec2i& _min, const McVec2i& _max) {
		p1 = ::mcmin(_min,_max);
		p2 = ::mcmax(_min,_max);
    }

    /// Set corners (min and max points).
    void setCorners(const McVec2i& _min, const McVec2i& _max) {
		setBounds(_min,_max);
    }

    /// Destructor.
    ~McBox2i()						{ }

    /// Get origins x coordinate.
    int& x()     { return p1.x;}
    /// Get origins y coordinate.
    int& y()     { return p1.y;}
    /// Get origins const x coordinate.
    const int& x()  const   { return p1.x;}
    /// Get origins const y coordinate.
    const int& y()  const   { return p1.y;}

    /// Returns minimal point
    McVec2i &	getMin() { return p1; }
    /// Returns maximal point
    McVec2i &	getMax() { return p2; }

    /// Returns minimal point (const).
    const McVec2i& getMin() const { return p1; }
    /// Returns maximal point (const).
    const McVec2i& getMax() const { return p2; }

    /// Returns the center of a box
    McVec2i getCenter() {return (p1+p2)/2;}

    /// Returns width and height of the box.
    McVec2i getSize() const { return p2-p1+McVec2i(1,1); }

    /// Get width.
    int width() { return p2.x-p1.x+1;}
    /// Get height.
    int height(){ return p2.y-p1.y+1;}



    /// Move box to origin (@c x,@c y).
    void moveTo(int x,int y) {
	McVec2i d(x-p1.x,y-p1.y);
	p1+=d; p2+=d;
    }
    /// Move box to origin @c p.
    void moveTo(McVec2i p) {
	moveTo(p.x,p.y);
    }

    /// Move box.
    void move(int dx,int dy) {
	McVec2i d(dx,dy);
	p1+=d; p2+=d;
    }

    /// Computes intersection with other box.
    void clip(const McBox2i& other) {
	p1 = ::mcmax(p1,other.p1);
	p2 = ::mcmin(p2,other.p2);
    }

    ///Extends Box2i (if necessary) to contain given 2D point
    void insert(const McVec2i &pt) {
	extendBy(pt);
    }

    ///Extends Box2i (if necessary) to contain given 2D point
    void extendBy(const McVec2i &pt) {
	if (isEmpty())
	    p1 = p2 = pt;
	else {
	    if (pt.x>p2.x) p2.x = pt.x;
	    if (pt.x<p1.x) p1.x = pt.x;
	    if (pt.y>p2.y) p2.y = pt.y;
	    if (pt.y<p1.y) p1.y = pt.y;
	}
    }

    /// Extend box by some other box.
    void extendBy(const McBox2i& other) {
        if ( other.isEmpty() )
            return;

        if ( isEmpty() ) {
            *this = other;
            return;
        }

        p1 = ::mcmin(p1,other.p1);
        p2 = ::mcmax(p2,other.p2);
    }

    // Extends Box2i (if necessary) to contain given Box2i
    //void	extendBy(const McBox2i &r);

    /// Returns TRUE if intersection of given point and Box2i is not empty
    int intersect(const McVec2i &pt) const {
	return (pt.x>=p1.x && pt.x<=p2.x && pt.y>=p1.y && pt.y<=p2.y);
    }

    /// Returns TRUE if intersection of given point and Box2i is not empty
    int contains(const McVec2i &pt) const {
	return intersect(pt);
    }

    /// Returns TRUE if intersection of given Box2i and Box2i is not empty
    int intersects(const McBox2i &bb) const {
	if (isEmpty() || bb.isEmpty()) return 0;
	if (bb.p2.x<p1.x || bb.p1.x>p2.x ||
	    bb.p2.y<p1.y || bb.p1.y>p2.y) return 0;
	return 1;
    }

    /// Sets rect to contain nothing
    void	makeEmpty() {
	p1.x=1; p2.x=0;
	p1.y=1; p2.y=0;
    }

    /** Checks if the box is empty (degenerate)	 */
    int isEmpty() const	{ return (p2.x < p1.x || p2.y<p1.y); }

    /// Checks if the box has area; i.e., both dimensions have positive size
    int hasArea() const
	{ return (p2[0] > p1[0] && p2[1] > p1[1]); }

    /// Is equal.
    int operator==(const McBox2i& o) {
	return p1==o.p1 && p2==o.p2;
    }
    /// Is not equal.
    int operator!=(const McBox2i& o) {
	return !(*this==o);
    }


    // Equality comparisons
    //friend int          operator ==(const McBox2i &b1, const McBox2i &b2);
    //friend int          operator !=(const McBox2i &b1, const McBox2i &b2)
    //	{ return !(b1 == b2); }

    // Minimum and maximum points
    McVec2i	p1, p2;
};

#endif

/// @}
