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

/// @addtogroup hxsegy hxsegy
/// @{
#ifndef READSEGY_H
#define READSEGY_H

struct SEGY_REEL {
  char       	ebcdic[3200]; 
  /*
  int           jobid;              // &header[0]
  int           line;               // &header[4]
  int           reeln;              // &header[8]
  short	        ntr;                // &header[12]
  short 	naux;               // &header[14]
  short 	nsi;                // &header[16]
  short 	nsiField;           // &header[18]
  short 	nsamp;              // &header[20] -> hns
  short 	nsampField;         // &header[22]
  short 	format;             // &header[24]
  short 	fold;
  short 	sort;
  short 	sum;
  short 	sweepStrart;
  short 	sweepEnd;
  short 	sweepLength;
  short 	sweepType;
  short 	sweepChannel;
  short 	sweepTaperStart;
  short 	sweepTaperEnd;
  short 	sweepTaperType;
  short 	correlated;
  short 	gain;
  short 	recovery;
  short 	measurement;
  short 	signal; 
  short 	vibratory;
  long 	        type;
  long 	        distance;
  long		unused[83];
  */

  int jobid;	/* job identification number */

  int lino;	/* line number (only one line per reel) */

  int reno;	/* reel number */

  short ntrpr;	/* number of data traces per record */

  short nart;	/* number of auxiliary traces per record */

  unsigned short hdt; /* sample interval in micro secs for this reel */

  unsigned short dto; /* same for original field recording */

  unsigned short hns; /* number of samples per trace for this reel */

  unsigned short nso; /* same for original field recording */

  short format;	/* data sample format code:
                0 = fixed point (1 bytes)
                1 = floating point (4 bytes)
                2 = fixed point (4 bytes)
                3 = fixed point (2 bytes)
                4 = fixed point w/gain code (4 bytes)
                5 = floating point IEEE (4 bytes)
                6 = signed integer (1 byte)
                7 = Not currently used
                8 = two's complement integer (1 byte) */

  short fold;	/* CDP fold expected per CDP ensemble */

  short tsort;	/* trace sorting code:
               -1 = Other
                0 = unknown
                1 = as recorded (no sorting)
                2 = CDP ensemble
                3 = single fold continuous profile
                4 = horizontally stacked
                5 = Common source
                6 = Common receiver
                7 = Common offset
                8 = Common mid-point */

  short vscode;	/* vertical sum code:
                1 = no sum
                2 = two sum ...
                N = N sum (N = 32,767) */

  short hsfs;	/* sweep frequency at start */

  short hsfe;	/* sweep frequency at end */

  short hslen;	/* sweep length (ms) */

  short hstyp;	/* sweep type code:
                1 = linear
                2 = parabolic
                3 = exponential
                4 = other */

  short schn;	/* trace number of sweep channel */

  short hstas;	/* sweep trace taper length at start if
                tapered (the taper starts at zero time
                and is effective for this length) */

  short hstae;	/* sweep trace taper length at end (the ending
                taper starts at sweep length minus the taper
                length at end) */

  short htatyp;	/* sweep trace taper type code:
                1 = linear
                2 = cos-squared
                3 = other */

  short hcorr;	/* correlated data traces code:
                1 = no
                2 = yes */

  short bgrcv;	/* binary gain recovered code:
                1 = yes
                2 = no */

  short rcvm;	/* amplitude recovery method code:
              1 = none
              2 = spherical divergence
              3 = AGC
              4 = other */

  short mfeet;	/* measurement system code:
                1 = meters
                2 = feet */

  short polyt;	/* impulse signal polarity code:
                1 = increase in pressure or upward
                geophone case movement gives
                negative number on tape
                2 = increase in pressure or upward
                geophone case movement gives
                positive number on tape */

  short vpol;	/* vibratory polarity code:
              code	seismic signal lags pilot by
              1	337.5 to  22.5 degrees
              2	 22.5 to  67.5 degrees
              3	 67.5 to 112.5 degrees
              4	112.5 to 157.5 degrees
              5	157.5 to 202.5 degrees
              6	202.5 to 247.5 degrees
              7	247.5 to 292.5 degrees
              8	293.5 to 337.5 degrees */

  short hunass1[120];	/* unassigned */

  unsigned short formatRevisionNumber; /* SEG Y Format Revision Number, 0x0100 for revision 1.0 */
  
  short fixedLengthTraceFlag; /*
                              1 : all traces in this SEG Y file are guaranteed to have the same
                                  sample interval and number of samples, as specified in hdt and hns.
                              2 : the length of the traces in the file may vary and the number of
                                  samples in ns of the Trace Header must be examined to determine the
                                  actual length of each trace.
                              */
  short numTextHeaderExt; /* Number of 3200-byte Textual Header Extension records following the Binary Header */

  short hunass2[47];	/* unassigned */
};

#define SHOTSORT 1
#define CDPSORT 2
#define STACKSORT 4
#define GEOPHONESORT 5
#define FCSNSORT 6
#define OFFSETSORT 7

#define REELBYTES 3600
#define HDRBYTES 240

#define FIRST_SYTRACE 1
#define LAST_SYTRACE -1

struct SEGY_TRACE {
   /*
   int 	        TLSN;               // &header[0]
   int 	        TRSN;               // &header[4]
   int 	        OIDN;               // &header[8]
   int 	        FCSN;               // &header[12]
   int		ESPN;
   int 	        SDPN;
   int		cdpn;       
   short	trid;
   short	nvsum;
   short	nhsum;
   short 	use;
   int 	        offset;
   int		relev;
   int		selev;
   int		sdepth;
   int		relevDatum;
   int		selevDatum;
   int		swater;
   int 	        rwater;
   short 	elevScaler;
   short 	coordScaler;
   int 	        Sx;
   int		Sy;
   int		Gx;
   int		Gy;
   short	units;
   short	weathering;
   short 	subweathering;
   short	suphole;
   short	guphole;
   short 	sStatic;
   short 	gStatic; 
   short	totalStatic;
   short 	lagA;
   short	lagB;
   short 	delay;
   short	muteStart;
   short	muteEnd;
   short 	nsampTr;
   short 	nsiTr;
   short 	gainType;
   short 	gainConstant;
   short 	gaininitial;
   short 	correlated;
   short 	sweepStart;
   short 	sweepEnd;
   short 	sweepLength;
   short 	sweepType;
   short 	sweepTaperStart;
   short 	sweepTaperEnd;
   short 	sweepTaperType;
   short 	unused1;
   short 	datumElev;
   short 	unused2;
   short 	unused3;
   short	unused4;
   short 	unused5;
   short 	unused6;
   short 	unused7;
   short 	yearRecorded;
   short	dayRecored;
   short 	unused8;
   short 	unused9;
   short 	unused10;
   short 	unused11;
   short 	unused12;
   short 	unused13;
   short  	geonum1;
   short 	geonumlast;
   short        gapSize;
   short 	unused14;
   int 	        SGEN;
   int		SSPN;
   int 	        DPLO;
   int		LAST;
   int 	        FSPN;
   int		SGID;
   int		VELO;
   int		FOLD;
   int 	        SCAL;
   short	plotId1;
   short	plotId2;
   short        CDPelev;
   short 	unused15;
   int 	        unused16;
   int		unused17;
   int		unused18;
   int 	        plotLabel;
   float 	data[1];
   */

  int tracl;	/* trace sequence number within line */

  int tracr;	/* trace sequence number within reel */

  int fldr;	/* field record number */

  int tracf;	/* trace number within field record */

  int ep;	/* energy source point number */

  int cdp;	/* CDP ensemble number */

  int cdpt;	/* trace number within CDP ensemble */

  short trid;	/* trace identification code:
              1 = seismic data
              2 = dead
              3 = dummy
              4 = time break
              5 = uphole
              6 = sweep
              7 = timing
              8 = water break
              9---, N = optional use (N = 32,767)

              Following are CWP id flags:

              9 = autocorrelation

              10 = Fourier transformed - no packing
              xr[0],xi[0], ..., xr[N-1],xi[N-1]

              11 = Fourier transformed - unpacked Nyquist
              xr[0],xi[0],...,xr[N/2],xi[N/2]

              12 = Fourier transformed - packed Nyquist
              even N:
              xr[0],xr[N/2],xr[1],xi[1], ...,
              xr[N/2 -1],xi[N/2 -1]
              (note the exceptional second entry)
              odd N:
              xr[0],xr[(N-1)/2],xr[1],xi[1], ...,
              xr[(N-1)/2 -1],xi[(N-1)/2 -1],xi[(N-1)/2]
              (note the exceptional second & last entries)

              13 = Complex signal in the time domain
              xr[0],xi[0], ..., xr[N-1],xi[N-1]

              14 = Fourier transformed - amplitude/phase
              a[0],p[0], ..., a[N-1],p[N-1]

              15 = Complex time signal - amplitude/phase
              a[0],p[0], ..., a[N-1],p[N-1]

              16 = Real part of complex trace from 0 to Nyquist

              17 = Imag part of complex trace from 0 to Nyquist

              18 = Amplitude of complex trace from 0 to Nyquist

              19 = Phase of complex trace from 0 to Nyquist

              21 = Wavenumber time domain (k-t)

              22 = Wavenumber frequency (k-omega)

              23 = Envelope of the complex time trace

              24 = Phase of the complex time trace

              25 = Frequency of the complex time trace

              30 = Depth-Range (z-x) traces

              43 = Seismic Data, Vertical Component 

              44 = Seismic Data, Horizontal Component 1 

              45 = Seismic Data, Horizontal Component 2 

              46 = Seismic Data, Radial Component

              47 = Seismic Data, Transverse Component  

              101 = Seismic data packed to bytes (by supack1)

              102 = Seismic data packed to 2 bytes (by supack2)
              */

  short nvs;	/* number of vertically summed traces (see vscode
              in bhed structure) */

  short nhs;	/* number of horizontally summed traces (see vscode
              in bhed structure) */

  short duse;	/* data use:
              1 = production
              2 = test */

  int offset;	/* distance from source point to receiver
              group (negative if opposite to direction
              in which the line was shot) */

  int gelev;	/* receiver group elevation from sea level
              (above sea level is positive) */

  int selev;	/* source elevation from sea level
              (above sea level is positive) */

  int sdepth;	/* source depth (positive) */

  int gdel;	/* datum elevation at receiver group */

  int sdel;	/* datum elevation at source */

  int swdep;	/* water depth at source */

  int gwdep;	/* water depth at receiver group */

  short scalel;	/* scale factor for previous 7 entries
                with value plus or minus 10 to the
                power 0, 1, 2, 3, or 4 (if positive,
                multiply, if negative divide) */

  short scalco;	/* scale factor for next 4 entries
                with value plus or minus 10 to the
                power 0, 1, 2, 3, or 4 (if positive,
                multiply, if negative divide) */

  int  sx;	/* X source coordinate */

  int  sy;	/* Y source coordinate */

  int  gx;	/* X group coordinate */

  int  gy;	/* Y group coordinate */

  short counit;	/* coordinate units code:
                for previous four entries
                1 = length (meters or feet)
                2 = seconds of arc (in this case, the
                X values are longitude and the Y values
                are latitude, a positive value designates
                the number of seconds east of Greenwich
                or north of the equator
                3 = decimal degrees
                4 = degrees, minutes, seconds */

  short wevel;	/* weathering velocity */

  short swevel;	/* subweathering velocity */

  short sut;	/* uphole time at source */

  short gut;	/* uphole time at receiver group */

  short sstat;	/* source static correction */

  short gstat;	/* group static correction */

  short tstat;	/* total static applied */

  short laga;	/* lag time A, time in ms between end of 240-
              byte trace identification header and time
              break, positive if time break occurs after
              end of header, time break is defined as
              the initiation pulse which maybe recorded
              on an auxiliary trace or as otherwise
              specified by the recording system */

  short lagb;	/* lag time B, time in ms between the time break
              and the initiation time of the energy source,
              may be positive or negative */

  short delrt;	/* delay recording time, time in ms between
                initiation time of energy source and time
                when recording of data samples begins
                (for deep water work if recording does not
                start at zero time) */

  short muts;	/* mute time--start */

  short mute;	/* mute time--end */

  unsigned short ns;	/* number of samples in this trace */

  unsigned short dt;	/* sample interval; in micro-seconds */

  short gain;	/* gain type of field instruments code:
              1 = fixed
              2 = binary
              3 = floating point
              4 ---- N = optional use */

  short igc;	/* instrument gain constant */

  short igi;	/* instrument early or initial gain */

  short corr;	/* correlated:
              1 = no
              2 = yes */

  short sfs;	/* sweep frequency at start */

  short sfe;	/* sweep frequency at end */

  short slen;	/* sweep length in ms */

  short styp;	/* sweep type code:
              1 = linear
              2 = cos-squared
              3 = other */

  short stas;	/* sweep trace length at start in ms */

  short stae;	/* sweep trace length at end in ms */

  short tatyp;	/* taper type: 1=linear, 2=cos^2, 3=other */

  short afilf;	/* alias filter frequency if used */

  short afils;	/* alias filter slope */

  short nofilf;	/* notch filter frequency if used */

  short nofils;	/* notch filter slope */

  short lcf;	/* low cut frequency if used */

  short hcf;	/* high cut frequncy if used */

  short lcs;	/* low cut slope */

  short hcs;	/* high cut slope */

  short year;	/* year data recorded */

  short day;	/* day of year */

  short hour;	/* hour of day (24 hour clock) */

  short minute;	/* minute of hour */

  short sec;	/* second of minute */

  short timbas;	/* time basis code:
                1 = local
                2 = GMT
                3 = other
                4 = UTC */

  short trwf;	/* trace weighting factor, defined as 1/2^N
              volts for the least sigificant bit */

  short grnors;	/* geophone group number of roll switch
                position one */

  short grnofr;	/* geophone group number of trace one within
                original field record */

  short grnlof;	/* geophone group number of last trace within
                original field record */

  short gaps;	/* gap size (total number of groups dropped) */

  short otrav;	/* overtravel taper code:
                1 = down (or behind)
                2 = up (or ahead) */

  /*  */
  int cdpX;	/*  */

  int cdpY;	/*  */

  int inlineNumber;	/*  */

  int crosslineNumber;	/*  */

  int shotPointNumber;	/*  */

  short shotPointScale;	/*  */

  short tvmu; 	/* Trace value measurement unit */

  int transductionConstantM ;	/* Transduction Constant Mantissa */

  short transductionConstantP ;	/* Transduction Constant Power of ten */

  short transductionUnits ; /*  */

  short dtid;	/* Device/Trace Identifier */

  short tscale;	/*  */

  short unass[12];
};

#endif

/// @}
