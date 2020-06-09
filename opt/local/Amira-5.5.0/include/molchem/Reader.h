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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_READER_H
#define MOLCHEM_READER_H

#include "MolChemWinDLLApi.h"
#include <mclib/McString.h>

class McBitfield;

namespace molchem {

    class Logger;

    class MOLCHEM_API Reader {
    public:
        Reader();
        virtual ~Reader();
        /** Configures how the escape character '\' is interpreted. 
            With true, the '\' will be skipped and the following char will 
            always be interpreted as a token, even if it is a delimiter. 
            A '\' must thus be encoded as '\\'. With false (default) 
            it will be handled in the usual way. */
        void setUseEscape(bool esc);
        /** Configures the delimiters. Each charackter in str will be handled as
            a delimiter. */
        void setDelimiters(const char* str);
        // reads n charackters or less if eof encountered
        const McString& readNChars(int n);
        // reads a token until it finds a delimiter, or an eof (not consumed)
        const McString& nextToken();
        // reads a line until it finds a new line (new line chars are consumed)
        const McString& nextLine();
        // skips all delimiters until first non delimiter char (not consumed) or eof
        void skipSpace();
        // are there any more charackters in the stream ?
        bool eos() {return stream_eos();}
        // Returns file position
        long getPos();
        // Sets file position
        void setPos(long);
        char peek();
        // skips the n next lines
        void skipLines(int n);
        // skips all lines until the beginning of a line is equal to str. Sets position behind the matched string. Returns false if string was not found
        bool skipToLine(char *str);
    protected:
        virtual long stream_tell() = 0;
        virtual void stream_seek(long p) = 0;
        virtual char stream_getc() = 0;
        virtual void stream_ungetc(char c) = 0;
        virtual bool stream_eos() = 0;
        // Returns whether charackter is a delimiter
        bool isDelimiter(char c);
        // The currently read token
        McString token;
        /* contains 256 entries, one for each ascii charackter. Defines which 
           chars act as delimiters. */
        McBitfield* delimiters;
        // Use '\' as an escape charackter ?
        bool useEscape; 
        // the logger
        static molchem::Logger* logger;
   };

    class MOLCHEM_API FileReader : public Reader {
    public:
        FileReader(FILE* file) {f=file;iseof=false;}
    protected:
        FILE* f;bool iseof;
        virtual long stream_tell() {return ftell(f);}
        virtual void stream_seek(long p) {iseof=false;fseek(f,p,SEEK_SET);}
        virtual char stream_getc() {char c=fgetc(f);if (c==EOF) {iseof=true;return 0;} return c;}
        virtual void stream_ungetc(char c) {ungetc(c,f);}
        virtual bool stream_eos() {return iseof;}
    };

    class MOLCHEM_API StringReader : public Reader {
    public:
        StringReader(const char* s) {str=s;pos=0;}
    protected:
        McString str;
        mculong pos;
        virtual long stream_tell() {return pos;}
        virtual void stream_seek(long p) { pos=p;}
        virtual char stream_getc() {if (stream_eos()) return 0; return str[(int)pos++];}
        virtual void stream_ungetc(char c) {pos--;}
        virtual bool stream_eos() { return pos>=str.length();}
    };
}


#endif

/// @}
