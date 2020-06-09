/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T. DUFOUR (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_VRSEGY_READER_
#define  _SO_VRSEGY_READER_

#include <VolumeViz/readers/SoVolumeReader.h>

struct SoVRSegyTraceIdHeader;

/**
 * @VREXT SEGY file trace header field description.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * This class allows describing the position, the length and the format of each field within a SEGY trace header.
 * (SEGY is a widely used format for storing seismic data). 
 * It is used to query this information from the SEGY file reader 
 * (see SoVRSegyFileReader::getSegyTraceHeader). See also SoVRSegyFileHeader.
 * 
 * 
 */
class VOLUMEVIZ_API SoVRSegyTraceHeaderBytePosition
{
 public:
  /**
   * constructor
   */
  SoVRSegyTraceHeaderBytePosition();

  /**
   * Field names
   */
  enum TraceAttribute {
    SEGY_TRACL,  // Trace sequence number within line
    SEGY_TRACR,  // Trace sequence number within reel
    SEGY_FLDR,   // Field record number
    SEGY_TRACF,  // Trace number within field record
    SEGY_EP,     // Energy source point number
    SEGY_CDP,    // CDP ensemble number
    SEGY_CDPT,   // Trace number within CDP ensemble
    SEGY_TRID,   // Trace identification code
    SEGY_NVS,    // Number of vertically summed traces
    SEGY_NHS,    // Number of horizontally summed traces
    SEGY_DUSE,   // Data use
    SEGY_OFFSET, // Distance from source point to receiver group
    SEGY_GELEV,  // Receiver group elevation from sea level
    SEGY_SELEV,  // Source elevation from sea level
    SEGY_SDEPTH, // Source depth (positive)
    SEGY_GDEL,   // Datum elevation at receiver group
    SEGY_SDEL,   // Datum elevation at source
    SEGY_SWDEP,  // Water depth at source
    SEGY_GWDEP,  // Water depth at receiver group
    SEGY_SCALEL, // Scale factor for previous 7 entries
    SEGY_SCALCO, // Scale factor for next 4 entries
    SEGY_SX,     // X source coordinate
    SEGY_SY,     // Y source coordinate
    SEGY_GX,     // X group coordinate
    SEGY_GY,     // Y group coordinate
    SEGY_COUNIT, // Coordinate units code
    SEGY_WEVEL,  // Weathering velocity
    SEGY_SWEVEL, // Subweathering velocity
    SEGY_SUT,    // Uphole time at source
    SEGY_GUT,    // Uphole time at receiver group
    SEGY_SSTAT,  // Source static correction
    SEGY_GSTAT,  // Group static correction
    SEGY_TSTAT,  // Total static applied
    SEGY_LAGA,   // Lag time A
    SEGY_LAGB,   // Lag time B
    SEGY_DELRT,  // Delay Record Time
    SEGY_MUTS,   // Mute time--start
    SEGY_MUTE,   // Mute time--end
    SEGY_NS,     // Number of samples in this trace
    SEGY_DT,     // Sample interval, in micro-seconds
    SEGY_GAIN,   // Gain type of field instruments code
    SEGY_IGC,    // Instrument gain constant
    SEGY_IGI,    // Instrument early or initial gain
    SEGY_CORR,   // Correlated
    SEGY_SFS,    // Sweep frequency at start
    SEGY_SFE,    // Sweep frequency at end
    SEGY_SLEN,   // Sweep length in ms
    SEGY_STYP,   // Sweep type code
    SEGY_STAS,   // Sweep trace length at start
    SEGY_STAE,   // Sweep trace length at end
    SEGY_TATYP,  // Taper type
    SEGY_AFILF,  // Alias filter frequency
    SEGY_AFILS,  // Alias filter slope
    SEGY_NOFILF, // Notch filter frequency 
    SEGY_NOFILS, // Notch filter slope
    SEGY_LCF,    // Low cut frequency
    SEGY_HCF,    // High cut frequncy
    SEGY_LCS,    // Low cut slope
    SEGY_HCS,    // High cut slope
    SEGY_YEAR,   // Year data recorded
    SEGY_DAY,    // Day of year
    SEGY_HOUR,   // Hour of day
    SEGY_MINUTE, // Minute of hour
    SEGY_SEC,    // Second of minute
    SEGY_TIMBAS, // Time basis code
    SEGY_TRWF,   // Trace weighting factor
    SEGY_GRNORS, // Geophone group number of roll switch position one
    SEGY_GRNOFR, // Geophone group number of trace one within original field record
    SEGY_GRNLOF, // Geophone group number of last trace within original field record
    SEGY_GAPS,   // Gap size
    SEGY_OTRAV,  // Overtravel taper code
    SEGY_CDPX,
    SEGY_CDPY,
    SEGY_INLINENUMBER,
    SEGY_CROSSLINENUMBER,
    SEGY_SHOTPOINTNUMBER,
    SEGY_SHOTPOINTSCALE,
    SEGY_TVMU,   // Trace value measurement unit
    SEGY_TRANSDUCTIONCONSTANTM,  // Transduction Constant Mantissa
    SEGY_TRANSDUCTIONCONSTANTP,  // Transduction Constant Power of ten
    SEGY_TRANSDUCTIONUNITS,
    SEGY_DTID,   // Device/Trace Identifier
    SEGY_TSCALE,

    SEGY_NUM_FIELDS,           // To count the number of fields
    SEGY_CROSSLINE = SEGY_CDP, // Synonym for the crossline position
    SEGY_INLINE = SEGY_TRACR   // Synonym for the inline position
  };

  /**
   * Field formats
   */
  enum TraceByteFormat {
    /** Field format is integer 8 bits. */
	  SEGY_INTEGER8_FORMAT,  
    /** Field format is integer 16 bits. */
	  SEGY_INTEGER16_FORMAT,
    /** Field format is integer 32 bits. */
	  SEGY_INTEGER32_FORMAT,
    /** Field format is IBM float. */
	  SEGY_IBM_FLOAT_FORMAT,
    /** Field format is IEEE float. */
	  SEGY_IEEE_FLOAT_FORMAT
  };

  /**
   * Sets/Gets the byte position of a specific attribute within the trace header.
   * For instance calling setBytePosition(TraceAttribute::SEGY_SX, 71) means that 
   * the attribute source coordinate X should be retreived at from the byte 
   * position 71 (instead of 73 by default).
   */
  void    setBytePosition( TraceAttribute attr, uint8_t position );
  uint8_t getBytePosition( TraceAttribute attr ) const;

  /**
   * Gets the field length of a specific attribute within the trace header.
   * Valid values are 1, 2, and 4 (char, short, int/ieee/ibm, respectively).
   */
  uint8_t getByteLength( TraceAttribute attr ) const;

  /**
   * Sets/Gets the field format of a specific attribute within the trace header.
   * The default format for all the fields is either SEGY_INTEGER16_FORMAT or SEGY_INTEGER32_FORMAT,
   * see the class SoVRSegyTraceIdHeader below.
   * For instance calling setByteFormat(TraceAttribute::SEGY_SX, SEGY_IEEE_FLOAT_FORMAT) means that 
   * the attribute source coordinate X should be coded as a IEEE float. 
   */
  void            setByteFormat( TraceAttribute attr, TraceByteFormat format );
  TraceByteFormat getByteFormat( TraceAttribute attr ) const;

  /**
   * Gets the value of a specific field.
   * The way the value is retrieved depends on its position and format. These parameters
   * might be specified by setBytePosition() and setByteFormat() respectively.
   */
  int getFieldValue( TraceAttribute attr, const SoVRSegyTraceIdHeader &trHdr ) const;

 SoINTERNAL public:
  void resetObject();

 protected:
  uint8_t         m_BytePos[SEGY_NUM_FIELDS];
  TraceByteFormat m_ByteFmt[SEGY_NUM_FIELDS];
};

/**
 * @VREXT SEGY file header.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * This class encapsulates the contents of a SEGY file header 
 * (SEGY is a widely used format for storing seismic data). 
 * It is used to query this information from the SEGY file reader 
 * (see SoVRSegyFileReader::getSegyFileHeader). See also SoVRSegyTraceIdHeader.
 * 
 * 
 */
struct SoVRSegyFileHeader 
{

 public:
  /** Job identification number */
  int jobid;
  /** Line number (only one line per reel) */
  int lino;
  /** Reel number */
  int reno;
  /** Number of data traces per record */
  short ntrpr;
  /** Number of auxiliary traces per record */
  short nart;
  /** Sample interval in micro secs for this reel */
  unsigned short hdt;
  /** Same for original field recording */
  unsigned short dto;
  /** Number of samples per trace for this reel */
  unsigned short hns;
  /** Same for original field recording */
  unsigned short nso;
  /** data sample format code: @BR
      0 = Fixed point (1 bytes)@BR
      1 = Floating point (4 bytes)@BR
      2 = Fixed point (4 bytes)@BR
      3 = Fixed point (2 bytes)@BR
      4 = Fixed point w/ gain code (4 bytes)@BR
      5 = Floating point IEEE (4 bytes)@BR
      6 = Signed integer (1 byte)@BR
      7 = Not currently used@BR
      8 = Two's complement integer (1 byte) */
  short format;
  /** CDP fold expected per CDP ensemble */
  short fold;
  /** Trace sorting code: @BR
     -1 = Other @BR
     0 = Unknown @BR
     1 = As recorded (no sorting) @BR
     2 = CDP ensemble @BR
     3 = Single fold continuous profile @BR
     4 = Horizontally stacked @BR
     5 = Common source @BR
     6 = Common receiver @BR
     7 = Common offset @BR
     8 = Common mid-point */
  short tsort;
  /** Vertical sum code:@BR
     1 = No sum@BR
     2 = Two sum... @BR
     N = N sum (N = 32,767) */
  short vscode;
  /** Sweep frequency at start */
  short hsfs;
  /** Sweep frequency at end */
  short hsfe;
  /** Sweep length (ms) */
  short hslen;
  /** Sweep type code:@BR
      1 = Linear@BR
      2 = Parabolic@BR
      3 = Exponential@BR
      4 = Other */
  short hstyp;
  /** Trace number of sweep channel */
  short schn;
  /** Sweep trace taper length at start if tapered (the taper starts at zero time
      and is effective for this length) */
  short hstas;
  /** Sweep trace taper length at end (the ending taper starts at sweep
      length minus the taper length at end) */
  short hstae;
  /** Sweep trace taper type code:@BR
      1 = Linear@BR
      2 = Cos-squared@BR
      3 = Other */
  short htatyp;
  /** Correlated data traces code:@BR
      1 = No@BR
      2 = Yes */
  short hcorr;
  /** Binary gain recovered code:@BR
      1 = Yes@BR
      2 = No
   */
  short bgrcv;
  /** Amplitude recovery method code:@BR
      1 = None@BR
      2 = Spherical divergence@BR
      3 = AGC@BR
      4 = Other */
  short rcvm;
  /** Measurement system code:@BR
      1 = Meters@BR
      2 = Feet */
  short mfeet;
  /** Impulse signal polarity code:@BR
      1 = Increase in pressure or upward geophone case movement gives
          negative number on tape@BR
      2 = Increase in pressure or upward geophone case movement gives
          positive number on tape */
  short polyt;
  /** Vibratory polarity code:

      @TABLE_FILE_FORMAT
      @TR Code  @TD Seismic signal lags pilot by
      @TR 1  @TD 337.5 to  22.5 degrees
      @TR 2  @TD 22.5 to  67.5 degrees
      @TR 3  @TD 67.5 to 112.5 degrees
      @TR 4  @TD 112.5 to 157.5 degrees
      @TR 5  @TD 157.5 to 202.5 degrees
      @TR 6  @TD 202.5 to 247.5 degrees
      @TR 7  @TD 247.5 to 292.5 degrees
      @TR 8  @TD 293.5 to 337.5 degrees 
      @TABLE_END 
  */

  short vpol;
  /** Unassigned */
  short hunass1[120];
  /** SEG Y Format Revision Number, 0x0100 for revision 1.0 */
  unsigned short formatRevisionNumber;
  /** Fixed trace length flag@BR
      1: All traces in this SEG Y file are guaranteed to have the same
          sample interval and number of samples, as specified in hdt and hns.@BR
      2: The length of the traces in the file may vary and the number of
          samples in ns of the Trace Header must be examined to determine the
          actual length of each trace. */  
  short fixedLengthTraceFlag;
  /** Number of 3200-byte Textual Header Extension records following
      the Binary Header */
  short numTextHeaderExt;
  /** Unassigned */
  short hunass2[47];
};


/**
 * @VREXT SEGY trace identification header.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * This class encapsulates the contents of a SEGY trace header 
 * (SEGY is a widely used format for storing seismic data). 
 * It is used to query this information from the SEGY file reader 
 * (see SoVRSegyFileReader::getSegyTraceHeader). See also SoVRSegyFileHeader.
 * 
 * 
 */
struct SoVRSegyTraceIdHeader
{

 public:
  /** Trace sequence number within line */
  int tracl;
  /** Trace sequence number within reel */
  int tracr;
  /** Field record number */
  int fldr;
  /** Trace number within field record */
  int tracf;
  /** Energy source point number */
  int ep;
  /** CDP ensemble number */
  int cdp;
  /** Trace number within CDP ensemble */
  int cdpt;
  /** Trace identification code:@BR
      1 = Seismic data @BR
      2 = Dead @BR
      3 = Dummy @BR
      4 = Time break @BR
      5 = Uphole @BR
      6 = Sweep @BR
      7 = Timing @BR
      8 = Water break @BR
      9...N = optional use (N = 32,767)

      Following are CWP id flags:

      9 = Autocorrelation

      10 = Fourier transformed - no packing @BR
      xr[0],xi[0], ..., xr[N-1],xi[N-1]

      11 = Fourier transformed - unpacked Nyquist @BR
      xr[0],xi[0],...,xr[N/2],xi[N/2]

      12 = Fourier transformed - packed Nyquist @BR
      even N: @BR
      xr[0],xr[N/2],xr[1],xi[1], ..., @BR
      xr[N/2 -1],xi[N/2 -1] @BR
      (note the exceptional second entry)

      odd N: @BR
      xr[0],xr[(N-1)/2],xr[1],xi[1], ..., @BR
      xr[(N-1)/2 -1],xi[(N-1)/2 -1],xi[(N-1)/2] @BR
      (note the exceptional second & last entries)

      13 = Complex signal in the time domain @BR
      xr[0],xi[0], ..., xr[N-1],xi[N-1]

      14 = Fourier transformed - amplitude/phase @BR
      a[0],p[0], ..., a[N-1],p[N-1]

      15 = Complex time signal - amplitude/phase @BR
      a[0],p[0], ..., a[N-1],p[N-1]

      16 = Real part of complex trace from 0 to Nyquist @BR
      17 = Imag part of complex trace from 0 to Nyquist @BR
      18 = Amplitude of complex trace from 0 to Nyquist @BR
      19 = Phase of complex trace from 0 to Nyquist @BR
      21 = Wavenumber time domain (k-t) @BR
      22 = Wavenumber frequency (k-omega) @BR
      23 = Envelope of the complex time trace @BR
      24 = Phase of the complex time trace @BR
      25 = Frequency of the complex time trace @BR
      30 = Depth-Range (z-x) traces @BR
      43 = Seismic Data, Vertical Component  @BR
      44 = Seismic Data, Horizontal Component 1  @BR
      45 = Seismic Data, Horizontal Component 2  @BR
      46 = Seismic Data, Radial Component @BR
      47 = Seismic Data, Transverse Component   @BR
      101 = Seismic data packed to bytes (by supack1) @BR
      102 = Seismic data packed to 2 bytes (by supack2) @BR
      */
  short trid;
  /** Number of vertically summed traces (see SoVRSegyFileHeader::vscode) */
  short nvs;
  /** Number of horizontally summed traces (see SoVRSegyFileHeader::SoVRSegyFileHeader) */
  short nhs;
  /** Data use: @BR
      1 = Production @BR
      2 = Test */
  short duse;
  /** Distance from source point to receiver group (negative if opposite to direction
      in which the line was shot) */
  int offset;
  /** Receiver group elevation from sea level (above sea level is positive) */
  int gelev;
  /** Source elevation from sea level (above sea level is positive) */
  int selev;
  /** Source depth (positive) */
  int sdepth;
  /** Datum elevation at receiver group */
  int gdel;
  /** Datum elevation at source */
  int sdel;
  /** Water depth at source */
  int swdep;
  /** Water depth at receiver group */
  int gwdep;
  /** Scale factor for previous 7 entries with value plus or minus 10 to the
      power 0, 1, 2, 3, or 4 (if positive, multiply, if negative divide) */
  short scalel;
  /** Scale factor for next 4 entries with value plus or minus 10 to the
      power 0, 1, 2, 3, or 4 (if positive, multiply, if negative divide) */
  short scalco;
  /** X source coordinate */
  int  sx;
  /** Y source coordinate */
  int  sy;
  /** X group coordinate */
  int  gx;
  /** Y group coordinate */
  int  gy;
  /** Coordinate units code: @BR
      For previous four entries @BR
      1 = Length (meters or feet) @BR
      2 = Seconds of arc (In this case, the
      X values are longitude and the Y values are latitude. A positive value designates
      the number of seconds east of Greenwich or north of the equator.) @BR
      3 = Decimal degrees @BR
      4 = Degrees, minutes, seconds */
  short counit;
  /** Weathering velocity */
  short wevel;
  /** Subweathering velocity */
  short swevel;
  /** Uphole time at source */
  short sut;
  /** Uphole time at receiver group */
  short gut;
  /** Source static correction */
  short sstat;
  /** Group static correction */
  short gstat;
  /** Total static applied */
  short tstat;
  /** Lag time A, time in ms between end of 240-
      byte trace identification header and time
      break, positive if time break occurs after
      end of header. Time break is defined as
      the initiation pulse which maybe recorded
      on an auxiliary trace or as otherwise
      specified by the recording system */
  short laga;
  /** Lag time B, time in ms between the time break
      and the initiation time of the energy source.
      May be positive or negative */
  short lagb;
  /** Delay recording time, time in ms between
      initiation time of energy source and time
      when recording of data samples begins
      (for deep water work if recording does not
      start at zero time) */
  short delrt;
  /** Mute time--start */
  short muts;
  /** Mute time--end */
  short mute;
  /** Number of samples in this trace */
  unsigned short ns;
  /** Sample interval; in micro-seconds */
  unsigned short dt;
  /** Gain type of field instruments code: @BR
      1 = Fixed @BR
      2 = Binary @BR
      3 = Floating point @BR
      4...N = optional use */
  short gain;
  /** Instrument gain constant */
  short igc;
  /** Instrument early or initial gain */
  short igi;
  /** Correlated: @BR
      1 = No @BR
      2 = Yes */
  short corr;
  /** Sweep frequency at start */
  short sfs;
  /** Sweep frequency at end */
  short sfe;
  /** Sweep length in ms */
  short slen;
  /** Sweep type code: @BR
      1 = Linear @BR
      2 = Cos-squared @BR
      3 = Other */
  short styp;
  /** Sweep trace length at start in ms */
  short stas;
  /** Sweep trace length at end in ms */
  short stae;
  /** Taper type:  @BR 1=linear,  @BR 2=cos^2,  @BR 3=other */
  short tatyp;
  /** Alias filter frequency if used */
  short afilf;
  /** Alias filter slope */
  short afils;
  /** Notch filter frequency if used */
  short nofilf;
  /** Notch filter slope */
  short nofils;
  /** Low cut frequency if used */
  short lcf;
  /** High cut frequncy if used */
  short hcf;
  /** Low cut slope */
  short lcs;
  /** High cut slope */
  short hcs;
  /** Year data recorded */
  short year;
  /** Day of year */
  short day;
  /** Hour of day (24 hour clock) */
  short hour;
  /** Minute of hour */
  short minute;
  /** Second of minute */
  short sec;
  /** Time basis code: @BR
      1 = Local @BR
      2 = GMT @BR
      3 = Other @BR
      4 = UTC */
  short timbas;
  /** Trace weighting factor, defined as 1/2^N volts for the least sigificant bit */
  short trwf;
  /** Geophone group number of roll switch position one */
  short grnors;
  /** Geophone group number of trace one within original field record */
  short grnofr;
  /** Geophone group number of last trace within original field record */
  short grnlof;
  /** Gap size (total number of groups dropped) */
  short gaps;
  /** Overtravel taper code: @BR
      1 = Down (or behind) @BR
      2 = Up (or ahead) */
  short otrav;
  /** X coordinate of ensemble (CDP) position of this trace */
  int cdpX;
  /** Y coordinate of ensemble (CDP) position of this trace */
  int cdpY;
  /** Inline-line number, for 3D poststack data. */
  int inlineNumber;
  /** Cross-line number, for 3D poststack data. */
  int crosslineNumber;
  /** Shotpoint number, for 2D poststack data. */
  int shotPointNumber;
  /** Scalar to be applied to shotPointNumber to give the real value */
  short shotPointScale;
  /** Trace value measurement unit 
      0 = Unknown
      1 = Pascal (Pa)
      2 = Volts (v)
      3 = Millivolts (mV)
      4 = Amperes (A)
      5 = Meters (m)
      6 = Meters per second (m/s)
      7 = Meters per second squared (m/s2)
      8 = Newton (N)
      9 = Watt (W) */
  short tvmu;
  /** Transduction Constant Mantissa */
  int transductionConstantM;
  /** Transduction Constant Power of ten */
  short transductionConstantP;
  /** Transduction Units
      0 = Unknown
      1 = Pascal (Pa)
      2 = Volts (v)
      3 = Millivolts (mV)
      4 = Amperes (A)
      5 = Meters (m)
      6 = Meters per second (m/s)
      7 = Meters per second squared (m/s2)
      8 = Newton (N)
      9 = Watt (W) */
  short transductionUnits;
  /** Device/Trace Identifier */
  short dtid;
  /** Scalar to be applied to - sut, gut, sstat, gstat, tstat, laga, lagb, delrt,
      muts, mute - header info to get the true time value in milliseconds. */
  short tscale;
  /** Unassigned */
  short unass[12];
};

#endif // _SO_VRSEGY_READER_
