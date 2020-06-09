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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GI_FRAMEBUFFER_H
#define GI_FRAMEBUFFER_H

#include <mclib/McDArray.h>
#include <mclib/McVec2i.h>
#include <mclib/McBox2i.h>

#include "HxGiWinDLLApi.h"
#include "GiSelection2D.h"

class Gi;
class GiShape;
class McEvent;
class GiViewer;
class QCursor;

/** Platform independent 2D frame buffer with drawing routines.

    This class provides a virtual framebuffer of arbitrary size. Only
    a subregion of the buffer does actually exist in memory. This
    subregion is called the physical buffer. All drawing routines
    render into the physical buffer. Derived classes can designed to
    display the physical buffer under a particular window system.
    There are only a few virtual function which has to be overloaded
    by a derived class. In particular these are setMemSize(), setOffset(),
    and paste().
*/
class HXSEGEDITOR_API GiFrameBuffer { 

  public:    
    /** Enumeration of supported pixel types:
        RGBA = 32 bit (24 used) e.g. Indigo2
	BGRA = 32 bit (24 used) onyx2, Intel-Linux
        ARGB = 32 bit (24 used) cross platform remote display
	ABGR = 32 bit (24 used) cross platform remote display
	P565 = 16 bit
    */
    enum PixelType { RGBA, BGRA, ARGB,ABGR, P565, P555 };

    /** Enumeration of supported draw functions. */
    enum Function { COPY, INVERT, XOR, SELECT };

    /** Public constructor. @c size specifies the size of the virtual
        framebuffer. @c memSize specifies the size of the physical
        buffer, i.e., the subregion used for the actual rendering.
        Usually this is the same as the window size. */
    GiFrameBuffer(const McVec2i& size, const McVec2i& memSize, PixelType);

    /// Destructor.
    virtual ~GiFrameBuffer();

    /// Resets current settings to their default values.
    void defaultValues();

    /// Returns size of physical buffer.
    const McVec2i& getMemSize() const { return memSize; }

    /// Returns size of virtual buffer.
    const McVec2i& getVirtSize() const { return virtSize; }

    /// Returns size of original image.
    const McVec2i& getOriginalSize() const { return originalSize; }
    
    /** Reset size of virtual buffer. zoomShift=0 means no zoom,
      positive values mean enlarge image, negative values make the image
      smaller */      
    virtual void resize(const McVec2i& size,
			const int* pixelSizeX=0, const int* pixelSizeY=0);

    /// Reset size of physical buffer.
    virtual void setMemSize(const McVec2i& memSize);
    
    /// Returns lower left corner of physical buffer.
    const McVec2i& getOffset() const { return offset; } 

    /// Repositions physical buffer within virtual buffer.
    virtual void setOffset(const McVec2i& newOffset);

    ///
    int getBytesPerPixel() const { return bytesPerPixel; }

    ///
    PixelType getPixelType() const { return pixelType; }

    ///
    int getBytesPerMemLine() const { return bytesPerLine; }

    /// Returns pointer to physical buffer.
    void* getMemImage() { return memory; }
    
    /// Set current color.
    void setColor(int r,int g,int b);
    
    /// Set current line width.
    void setLineWidth(int width);

    /// Set current draw function.
    void setFunction(Function f);

    /// Set clip box for rendering.
    void setClipBox(const McBox2i& region);

    /// Set clip box to be the whole physical buffer.
    void unsetClipBox();

    /// Set user data to be used by shapes.
    void setUserData(void* userData) { this->userData = userData; }

    /// Returns user data.
    void* getUserData() const { return userData; }

    /// Sets pointer to gi.
    void setGi(Gi* gi);

    /// Returns pointer to gi.
    Gi* getGi() const { return theGi; }

    /// Add shape object to frame buffer.
    int addShape(GiShape* shape);

    /// Check whether specific shape object is in its list
    int hasShape(GiShape* shape);

    /// Remove shape object from frame buffer.
    int removeShape(GiShape* shape);
    
    /** Set a 2D selection. An active selection causes the shapes
        0,..,@c nShapesToBeModified to be drawn in highlight mode. This
	affects the methods fillRect(), drawLine(), drawEllipse(), 
	writePixel(), and putImageGrey8(). */
    void setSelection(GiSelection2D* selection, int nShapesToBeModified);

    /// Returns selection object of framebuffer
    GiSelection2D* getSelection() { return currentSelection; }
    
    /// Fill a rectangular region.
    void fillRect(int x1,int y1,int x2,int y2);
    void fillRect(const McVec2i& lowerLeft, const McVec2i& upperRight)
	{ fillRect(lowerLeft.x, lowerLeft.y, upperRight.x, upperRight.y); }
    
    // Draw an ellipse.
    void drawEllipse(int x0,int y0,float rx,float ry);
    void drawEllipse(const McVec2i& p, float rx, float ry)
	{ drawEllipse(p.x, p.y, rx, ry); }
    void drawStippleEllipse(int x0,int y0,float rx,float ry, float increment = 5, unsigned int Color2 = 0);


    // Draw a rectangle
    void drawRect(const McVec2i& center, const McVec2i& size);
    void drawStippleRect(const McVec2i& center, const McVec2i& size, float increment = 5, unsigned int Color2 = 0);

    /// Draw a single line segment.
    void drawLine(int x1,int y1,int x2,int y2);
    void drawLine(const McVec2i& p, const McVec2i& q)
	{ drawLine(p.x, p.y, q.x, q.y); }

    /// Write a single pixel.
    void writePixel(int x, int y);

    /// Write a single pixel.
    void writePixel(const McVec2i& p) { writePixel(p.x,p.y); }

    /** The image is drawn to the framebuffer. The image origin is assumed
        to be at position (0,0). The image is (potentially non-uniformly)
        zoomed to the current resolution.*/
    void putImageGrey8Zoomed(const unsigned int* image,
			     mculong width, mculong height, mculong imBytesPerLine);
        
    /// Redraws physical buffer, but does not display it.
    virtual void render(GiShape* notMe = NULL);
    
    /// Redraws parts of the physical buffer.
    virtual void render(const McBox2i& region, GiShape* notMe = NULL);
    
    /// Initializes physical buffer with 0.
    void clear();

    /// Copys buffer onto screen.
    virtual void paste();

    /// Copys parts of physical buffer onto screen.
    virtual void paste(const McBox2i&);

    McVec2i zoomf(const McVec2f& vec) const;

    McVec2f unzoomf(const McVec2i& vec) const;

    /// Zoom a floating point vector (image to framebuffer coordinates).
    inline McVec2i zoom(const McVec2f& vec) const {
	return McVec2i(zoomx((int)(vec.x+0.5)),zoomy((int)(vec.y+0.5)));
    }

    /// Zoom an integer box (image to framebuffer coordinates).
    inline McBox2i zoom(const McBox2i& box) const {
	McBox2i b; 
	McVec2i p2(pixelSize(box.p2));
	if (p2.x) p2.x--;
	if (p2.y) p2.y--;
	p2+=zoom(box.p2);
	b.setBounds(zoom(box.p1), p2);
	return b;
    }

    /// Unzoom an integer box (framebuffer to image coordinates).
    inline McBox2i unzoom(const McBox2i& box) const {
	McBox2i b; b.setBounds(unzoom(box.p1),unzoom(box.p2));
	return b;
    }

    /// Zoom an integer point (image to framebuffer coordinates).
    inline McVec2i zoom(const McVec2i& vec) const {
	return McVec2i(zoomx(vec.x),zoomy(vec.y));
    }

    /// Unzoom an integer point (framebuffer to image coordinates).
    inline McVec2i unzoom(const McVec2i& vec) const {
        return McVec2i(unzoomx(vec.x),unzoomy(vec.y));
    }

    /// Get zoomed width of pixel i,j
    int pixelSizeX(int x) const { 
	if (x>=0 && x<nReplicX.size())
	    return nReplicX[x];
	return 0;
    }

    /// Get zoomed height of pixel i,j
    int pixelSizeY(int y) const { 
	if (y>=0 && y<nReplicY.size())
	    return nReplicY[y];
	return 0;
    }

    /// Get zoomed size of pixel i,j
    McVec2i pixelSize(McVec2i p) const { 
	return McVec2i(pixelSizeX(p.x),pixelSizeY(p.y));
    }

    /** Unzoom an integer point (framebuffer to image coordinates). If
        the image pixel appears larger in the frame buffer (e.g. as a
        4 by 4 square), then offset gives the offset within this larger pixel. */
    inline void unzoomDetailed(McVec2i fb, McVec2i& src, McVec2i& o) const {
        fb -= offset;
        if (fb.x<0) fb.x=0;
        if (fb.x>=srcValuesX.size()) fb.x=srcValuesX.size()-1;
        if (fb.y<0) fb.y=0;
        if (fb.y>=srcValuesY.size()) fb.y=srcValuesY.size()-1;
        src.x = srcValuesX[fb.x];
        src.y = srcValuesY[fb.y];
        o.x = offsetValuesX[fb.x];
        o.y = offsetValuesY[fb.y];
    }

    // check whether point is inside the virtual coordinate range
    int isInside(McVec2i p) {
        return (p.x>=0 && p.x<virtSize.x && p.y>=0 && p.y<virtSize.y);
    }

    /// Zoom a single coordinate (image to framebuffer coordinates).
    inline int zoomx(const int& x) const {
	if (x<0)
            return zoomedCoordsX[0];
	if (x>=zoomedCoordsX.size())
	    return virtSize.x-1;
	return zoomedCoordsX[x];
    }

    /// Zoom a single coordinate (image to framebuffer coordinates).
    inline int zoomy(const int& y) const {
	if (y<0) 
	    return zoomedCoordsY[0];
	if (y>=zoomedCoordsY.size())
	    return virtSize.y-1;
	return zoomedCoordsY[y];
    }

    /// Unzoom a single coordinate (framebuffer to image coordinates).
    inline int unzoomx(int x) const {
	x -= offset.x;
	if (x<0) return srcValuesX[0];
	if (x>=srcValuesX.size())
	    return srcValuesX.last();
	return srcValuesX[x];
    }

    /// Unzoom a single coordinate (framebuffer to image coordinates).
    inline int unzoomy(int y) const {
	y -= offset.y;
	if (y<0) return srcValuesY[0];
	if (y>=srcValuesY.size())
	    return srcValuesY.last();
	return srcValuesY[y];
    }
    
    ///
    int handleEvent(McEvent*);
    
    /// 
    typedef int EventHandler(GiFrameBuffer*,McEvent*, void* userData);

    ///
    void addEventHandler(EventHandler*,void* userData);

    ///
    void removeEventHandler(EventHandler*);

    int maxAlpha;
    
    ///
    GiViewer* getViewer() {return viewer;}
    
    ///
    GiViewer* viewer;

    virtual void setFlip(int flipx, int flipy);

    void getFlip(int& fx, int& fy) { fx=flipx; fy=flipy; }

    virtual void setRotate(int rotccw, int rotcw);

    void rotate(int iangle, mculong& height, mculong& width, const unsigned char* imgIn, unsigned char* imgOut, McVec2i& size);

    void setScrollBars(int hasHB, int hasVB, 
		       GiFrameBuffer* hSlave, GiFrameBuffer *vSlave);

    virtual void setCursor(const QCursor& c);

    void setUserEventData(const McDArray<void*> & data){ eventUserData = data; }
    void setEventHandler(const McDArray<EventHandler*> & handlers){ eventHandler = handlers; }

    const McDArray<void*> & getUserEventData() const { return eventUserData; }
    const McDArray<EventHandler*> & getEventHandler() const { return eventHandler; }
    /// @return returns true if the framebuffer is browsing slices
    bool isBrowsing();
    /// should be set to true while browsing slices 
    /// in oder skip the hidden selction check
    void setBrowsing(bool isBrowsing);
  protected:
    GiFrameBuffer* horizontalSlave;
    GiFrameBuffer* verticalSlave;
    unsigned int hasHorSB:1;
    unsigned int hasVertSB:1;
    unsigned int disabled:1;
    bool flipx;
    bool flipy;
    bool rotangle;
    bool swapxy;

    void prepareCoordLookups1();
    void prepareCoordLookups2();

    /// List of shapes which render into the frame buffer.
    McDArray<GiShape*> shapes;
    McDArray<int> srcValuesX,srcValuesY,offsetValuesX,offsetValuesY;
    McDArray<int> nReplicX,nReplicY,zoomedCoordsX,zoomedCoordsY;
    McVec2i originalSize;	// Size of unzoomed image.
    McVec2i virtSize;		// Size of virtual buffer.
    McVec2i memSize;		// Size of physical buffer.
    McVec2i offset;		// Lower left corner of physical buffer.
    int bytesPerPixel;		// Usually 2 or 4
    mculong bytesPerLine;	// Length of a scan line
    PixelType pixelType;	// May be RGBA, ABGR, or P565
    char* memory;		// Pointer to physical buffer
    McBox2i clipBox;	        // No rendering is done outside this box
    int nShapesToBeModified;
    GiSelection2D* currentSelection;
    Gi* theGi;

    unsigned int blendRed,blendBlue,blendColorRGB[3];
    unsigned int currentColor,currentColorRGB[3];
    int currentLineWidth;
    Function currentFunction;
    void* userData;
    int multiViewerMode;
    McDArray<void*> eventUserData;
    McDArray<EventHandler*> eventHandler;
    
    /** This constructor should be used by derived classes only.
        It doesn't allocate any memory. */
    GiFrameBuffer();
    
    /// Scroll the data in the physical buffer.
    void scrollHorizontal(int dx);

    /// Scroll the data in the physical buffer.
    void scrollVertical(int dy);

    /// Initialize LUT for pseudo-coloring and masking.
    void initPackedColors();

    unsigned int alpha(int x, int y) { return currentSelection->get(x,y); }
    
    unsigned int blendRGB(unsigned int color, unsigned int alpha) {
        if (alpha) {
            const unsigned int a = maxAlpha; // opacity value of red selection
            const unsigned int b = 255-a; // inverse value
            const unsigned int c1 = (b*(color&0xff) + a*(blendRed&0xff))>>8;
            const unsigned int c2 = (b*(color&0xff00) + a*(blendRed&0xff00))>>16;
            const unsigned int c3 = (b*(color&0xff0000) + a*(blendRed&0xff0000))>>24;
            return (c3<<16) | (c2<<8) | c1;
        }
        return color;
    }
    
    friend class GiQViewer;
    friend class GiViewer;
    friend class HxImageViewer;

private:
    bool browsing;

};

#endif

/// @}
