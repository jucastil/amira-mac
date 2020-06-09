/*
 * JPEGLess.h
 *
 * ---------------------------------------------------------------
 *
 * Lossless JPEG compression and decompression algorithms.
 *
 * ---------------------------------------------------------------
 *               
 * It is based on the program originally named ljpgtopnm and pnmtoljpg.
 * Major portions taken from the Independetn JPEG Group' software, and
 * from the Cornell lossless JPEG code (the original copyright notices
 * for those packages appears below).
 *
 * ---------------------------------------------------------------
 *
 * This is the main routine for the lossless JPEG decoder.  Large
 * parts are stolen from the IJG code, so:
 *
 * Copyright (C) 1991, 1992, Thomas G. Lane.
 * Part of the Independent JPEG Group's software.
 * See the file Copyright for more details.
 *
 * Copyright (c) 1993 Brian C. Smith, The Regents of the University
 * of California
 * All rights reserved.
 * 
 * Copyright (c) 1994 Kongji Huang and Brian C. Smith.
 * Cornell University
 * All rights reserved.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF CORNELL
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * CORNELL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND CORNELL UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

/* includes */

/* Global variables for lossless encoding process */

extern int  psvSet[7];       /* the PSV (prediction selection value) set    */
extern int  numSelValue;     /* number of PSVs in psvSet                    */
extern long outputFileBytes; /* the output file size in bytes               */
extern long totalHuffSym[7]; /* total bits of category symbols for each PSV */
extern long totalAddBits[7]; /* total bits of additional bits for each PSV  */


/*
 * read a JPEG lossless (8 or 16 bit) image in a file and decode it
 */
#ifdef __cplusplus
extern "C"  {
#endif

extern void JPEGLosslessDecodeImage (void* inBuf, unsigned short *image16, 
                                     int depth, unsigned long length);

}
