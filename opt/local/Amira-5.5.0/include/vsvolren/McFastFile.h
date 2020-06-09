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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef CLASS_MCFASTFILE_H
#define CLASS_MCFASTFILE_H

#include <mclib/McString.h>
#include <mclib/McPrimType.h>
#include <mclibthreaded/McWorkerThread.h>
#include <mclibthreaded/McThread.h>

#include "VsFFSInfoFile.h"
#include "VsFFSPacket.h"
#include "VsFFSPacketInStream.h"
#include "VsFFSPacketOutStream.h"

#define RECV_TMP_BUFFER                 1024 * 512
#define SEND_RECV_BUFFER_SIZE_CLIENT    (65536*8)

#if !defined(WIN32) && !defined(VS_MEDTRONIC_VISAGE_WS_DTI) && !defined(HX_OS_MACX)
    #define ffs_mask cpu_set_t
#else
    #define ffs_mask unsigned long
#endif

class McFastFile
{
public:

    McFastFile();

    virtual ~McFastFile();

    /**
        test for a fast file transfer after McFastFile_open
    */
    bool isFastTransfer( void );

    /**
        open a file.
        try to establis a FFS connection

        a_forceSAMBA = true   > use the fallback
                     = false  > try the fast transfer
    */
    bool open( char * a_filename, bool a_forceSAMBA = false );

    /**
        set the filepointer

        a_origin = SEEK_CUR / SEEK_BEGIN / SEEK_END

    */
    void seek( mcint64 a_distance, int a_origin );

    /**

        report the filepointer

    */
    void ftell( mcint64 & a_position );

    /**
        report the filesize
    */
    void size( mcuint64 & a_size );

    /**

        read from file

    */
    mcuint64 read( char * a_buffer, mcuint64 a_len );

    /**

        close the file

    */
    void close();

private:


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class SocketReaderThread : private McWorkerThread, public VsFFSPacketInStream
    {
    public:
        SocketReaderThread( int a_connection, mcuint64 a_fileSize, ffs_mask & a_cpuMask );
        virtual ~SocketReaderThread();

        void    SocketReaderThread_start(   int         a_packetSize,
                                                        int         a_firstPacketSize,
                                                        int         a_blockCount,
                                                        char *      a_userBuffer,
                                                        mcuint64    a_userBufferLength,
                                                        mcuint64    a_requestSize );
        void        SocketReaderThread_wait();
        mcuint64    SocketReaderThread_getReadBytes(){ return m_bytesRead; }

    protected:
        virtual void compute();
        virtual void do_computing();

    private:
        ffs_mask                m_cpuMask;
        mcuint64                m_requestSize,
                                m_fileSize,
                                m_bytesRead,
                                m_userBufferLength;
        int                     m_socket,
                                m_firstPacketSize,
                                m_packetSize,
                                m_blockCount;
        char *                  m_userBuffer;
        VsFFSBuffer             m_buffer,
                                m_data;
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    McMemArray<SocketReaderThread *> m_readerThreads;
    bool                                        m_fastTransfer;

    VsFFSInfoFile                               m_infoFile;

    McMemArray<int>                             m_connections;
    McMemArray<ffs_mask>                        m_cpuMask;
    VsFFSPacketInStream                         m_inStream;
    VsFFSPacketOutStream                        m_outStream;

    int                     m_verboseLevel,
                            m_file,
                            m_cmdThread,
                            m_cmdConnection;
    mcuint64                m_position,
                            m_size;

    /**

    check the filename for slash / backslash faults

    */
    void adjustSlashesInFilename( McString & a_filename );

    /**

    checks whether or not the filename is a UNC

    */
    bool isUNC( McString & a_filename );

    /**

    create the path to the server info file
    from the provided filename

    */
    void getInfoFileFromFilename( McString & a_filename, McString & a_infoFile );

    /**

    create the relative filepath
    from the provided filename

    */
    void getServerPathFromFilename( McString & a_filename, McString & a_serverFile );

    /**

    splits a file path to find the fast file server info file
    an parse it

    */
    bool readFastFileServerInfo( McString & a_filename );

    /**

    do the connection protocol

    */
    bool connectionHandshake( McString & a_filename, bool & a_operationSuccess );

    /**

    do the connection protocol

    */
    bool connect( McString & a_filename );

    /**

    adds a read thread for a connection

    */
    bool addThreadForConnection( int a_connection, mcuint64 a_size  );

    /**

    detects all cpu masks

    */
    bool detectCPUs( void );

/**

    gets the file position

    */
    mcuint64 tell( int a_file );

    /**

    prints something with respect to the verbose level

    */
    void FFS_printf( int a_level, char * fmtString, ... );

};

#endif

/// @}
