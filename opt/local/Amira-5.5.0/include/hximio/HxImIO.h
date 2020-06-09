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

/// @addtogroup hximio hximio
/// @{
#ifndef HX_IMIO_H
#define HX_IMIO_H

#include <stdarg.h>
#include <mclib/McTypedPointer.h>
#include <mclib/McPrimType.h>
#include <hximio/HxImIOWinDLLApi.h>

class QImage;
class HxRegColorField3;
class HxRegScalarField3;

class ProgressSenderIface;
extern "C" { // "C" binding allows easy access when linking dynamically

/**name Methods for 2D image IO */
//@{

/// Read an image from file, memory must be freed by user.
int HXIMIO_API readImage(const char* fn, int size[3], unsigned char*& data, const char* format=0);

/// Generic read method for 8 or 16-bit images, memory must be freed by user.
int HXIMIO_API readImage2(const char* fn, int size[3], McTypedPointer& data, const char* format=0);

/// Read a Qt image from file.
int HXIMIO_API readQImage(const char* fn, QImage& image, const char* format=0);

/// Return list of supported image output formats.
const HXIMIO_API char** imageOutputFormats(int& n);

/// Determine image format from file name suffix.
const HXIMIO_API char* queryImageFormat(const char* fn);

/// Write image to file, format is determined from suffix if last arg is 0.
int HXIMIO_API writeImage(const char* fn, const int size[3], const unsigned char* data, const char* format=0);

/// Write Qt image to file, format is determined from suffix if last arg is 0.
int HXIMIO_API writeQImage(const char* fn, const QImage& image, const char* format=0);

//@}

extern HXIMIO_API
int imIOignoreColormap;

} // extern "C"

int HXIMIO_API readTIF(const char*, int size[3], McTypedPointer& data);
int HXIMIO_API writeTIF(const char*, const int size[3], McTypedPointer data);

int HXIMIO_API readTIF(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readSGI(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readJPG(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readPPM(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readXPM(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readBMP(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readPNG(const char*, int size[3], unsigned char*& data);
int HXIMIO_API readRAW(const char*, int size[3], McPrimType inType, unsigned char*& data);

int HXIMIO_API writeTIF(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writeSGI(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writeJPG(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writePPM(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writeXPM(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writeBMP(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writePNG(const char*, const int size[3], const unsigned char* data);
int HXIMIO_API writeEPS(const char*, const int size[3], const unsigned char* data);

int HXIMIO_API readTIF(const char*, QImage& image);
int HXIMIO_API readSGI(const char*, QImage& image);
int HXIMIO_API readJPG(const char*, QImage& image);
int HXIMIO_API readPPM(const char*, QImage& image);
int HXIMIO_API readXPM(const char*, QImage& image);
int HXIMIO_API readBMP(const char*, QImage& image);
int HXIMIO_API readPNG(const char*, QImage& image);

int HXIMIO_API writeTIF(const char*, const QImage& image);
int HXIMIO_API writeSGI(const char*, const QImage& image);
int HXIMIO_API writeJPG(const char*, const QImage& image);
int HXIMIO_API writePPM(const char*, const QImage& image);
int HXIMIO_API writeXPM(const char*, const QImage& image);
int HXIMIO_API writeBMP(const char*, const QImage& image);
int HXIMIO_API writePNG(const char*, const QImage& image);
int HXIMIO_API writeEPS(const char*, const QImage& image);

int HXIMIO_API readTIF(int n, const char** files);
int HXIMIO_API readSGI(int n, const char** files);
int HXIMIO_API readJPG(int n, const char** files);
int HXIMIO_API readPPM(int n, const char** files);
int HXIMIO_API readXPM(int n, const char** files);
int HXIMIO_API readBMP(int n, const char** files);
int HXIMIO_API readPNG(int n, const char** files);

int HXIMIO_API readTIF(int n, const char** files, ProgressSenderIface *progress=0);
int HXIMIO_API readSGI(int n, const char** files, ProgressSenderIface *progress=0);
int HXIMIO_API readJPG(int n, const char** files, ProgressSenderIface *progress=0);
int HXIMIO_API readPPM(int n, const char** files, ProgressSenderIface *progress=0);
int HXIMIO_API readXPM(int n, const char** files, ProgressSenderIface *progress=0);
int HXIMIO_API readBMP(int n, const char** files, ProgressSenderIface *progress=0);
int HXIMIO_API readPNG(int n, const char** files, ProgressSenderIface *progress=0);

int HXIMIO_API writeTIF(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writeSGI(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writeJPG(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writePPM(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writeXPM(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writeBMP(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writePNG(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writeEPS(HxRegScalarField3* field, const char* filename);

int HXIMIO_API writeTIF(HxRegColorField3* field, const char* filename);
int HXIMIO_API writeSGI(HxRegColorField3* field, const char* filename);
int HXIMIO_API writeJPG(HxRegColorField3* field, const char* filename);
int HXIMIO_API writePPM(HxRegColorField3* field, const char* filename);
int HXIMIO_API writeXPM(HxRegColorField3* field, const char* filename);
int HXIMIO_API writeBMP(HxRegColorField3* field, const char* filename);
int HXIMIO_API writePNG(HxRegColorField3* field, const char* filename);
int HXIMIO_API writeEPS(HxRegColorField3* field, const char* filename);

class HxLattice;
int HXIMIO_API writePNG(HxLattice* lattice, const char* filename);

int HXIMIO_API writeTIF3D(HxRegScalarField3* field, const char* filename);
int HXIMIO_API writeTIF3D(HxRegColorField3* field, const char* filename);
int HXIMIO_API hxReadLeicaSlices(const char* file);
int HXIMIO_API hxReadStackedSlices(const char *file);
int HXIMIO_API hxReadLIF(int num, const char** files);

#ifdef HX_OS_WIN
int HXIMIO_API hxReadZVI(const char *file);
#endif

int HXIMIO_API readImages(int n, const char** files, const char* format, ProgressSenderIface *progress=0);
int HXIMIO_API writeImages(HxRegScalarField3*, const char* fn, const char* format);
int HXIMIO_API writeImages(HxRegColorField3*, const char* fn, const char* format);

void HXIMIO_API toQImage(const int size[3], const unsigned char* data, QImage& image);
void HXIMIO_API fromQImage(const QImage& image, int size[3], unsigned char*& data);

void HXIMIO_API amiraTIFFErrorHandler(const char*, const char*, va_list);

#endif

/// @}
