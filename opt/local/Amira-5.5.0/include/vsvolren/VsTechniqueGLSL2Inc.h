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
if ( name == "default" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/default.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/default.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "LINEREN-SHADED" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/LINEREN-SHADED.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/LINEREN-SHADED.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "setDepth" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/setDepth.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/setDepth.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techDepthPeel" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techDepthPeel.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techDepthPeel.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techRestoreFB" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techRestoreFB.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techRestoreFB.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techSlice" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSlice.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSlice.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techSliceContour" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceContour.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceContour.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techSliceRegion" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceRegion.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceRegion.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techSliceRGB" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceRGB.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceRGB.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "techSliceSelection" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceSelection.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/techSliceSelection.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "TridelityCompose" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/TridelityCompose.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/TridelityCompose.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "TridelityCompose2" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/TridelityCompose2.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/TridelityCompose2.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "TridelityCompose2view" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/TridelityCompose2view.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/TridelityCompose2view.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-DRR" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-DRR.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-DRR.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-DRR_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-DRR_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-DRR_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-DRR_POST" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-DRR_POST.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-DRR_POST.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-MIP-MIP" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP-MIP.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP-MIP.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-MIP-MIP_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP-MIP_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP-MIP_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-MIP" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-MIP_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-MIP_MM_POST" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP_MM_POST.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-MIP_MM_POST.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SSD" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SSD_POST" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD_POST.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD_POST.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SSD_RT8" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD_RT8.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD_RT8.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SSD_RT8_POST" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD_RT8_POST.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SSD_RT8_POST.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT-SVRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-SVRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-SVRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT-SVRT_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-SVRT_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-SVRT_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT-VRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-VRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-VRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT-VRT_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-VRT_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT-VRT_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_CAP-SVRT_CAP" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-SVRT_CAP.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-SVRT_CAP.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_CAP-SVRT_MM_CAP" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-SVRT_MM_CAP.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-SVRT_MM_CAP.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_CAP-VRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-VRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-VRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_CAP-VRT_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-VRT_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP-VRT_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_CAP" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_CAP.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_MM-VRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM-VRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM-VRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_MM_CAP-VRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM_CAP-VRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM_CAP-VRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-SVRT_MM_CAP" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM_CAP.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-SVRT_MM_CAP.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-VRT-VRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT-VRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT-VRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-VRT-VRT_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT-VRT_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT-VRT_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-VRT" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-VRT_DRR_RT8_POST" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT_DRR_RT8_POST.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT_DRR_RT8_POST.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           
if ( name == "VOLREN-VRT_MM" )                                   
{                                                          
    static unsigned char v[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT_MM.v"   
    };                                                     
    static unsigned char f[] =                             
    {                                                      
        #include "./share/vsvolren/glsl/include/VOLREN-VRT_MM.f"   
    };                                                     
    ov=v;                                                  
    of=f;                                                  
    ovLen = sizeof(v);                                   
    ofLen = sizeof(f);                                   
    break;                                                 
}                                                          
                                                           

/// @}
