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

/// @addtogroup exlibtiff exlibtiff
/// @{
#define UV_SQSIZ	(float)0.003500
#define UV_NDIVS	16289
#define UV_VSTART	(float)0.016940
#define UV_NVS		163
static struct {
	float	ustart;
	short	nus, ncum;
}	uv_row[UV_NVS] = {
	{ (float)0.247663,	4,	0 },
	{ (float)0.243779,	6,	4 },
	{ (float)0.241684,	7,	10 },
	{ (float)0.237874,	9,	17 },
	{ (float)0.235906,	10,	26 },
	{ (float)0.232153,	12,	36 },
	{ (float)0.228352,	14,	48 },
	{ (float)0.226259,	15,	62 },
	{ (float)0.222371,	17,	77 },
	{ (float)0.220410,	18,	94 },
	{ (float)0.214710,	21,	112 },
	{ (float)0.212714,	22,	133 },
	{ (float)0.210721,	23,	155 },
	{ (float)0.204976,	26,	178 },
	{ (float)0.202986,	27,	204 },
	{ (float)0.199245,	29,	231 },
	{ (float)0.195525,	31,	260 },
	{ (float)0.193560,	32,	291 },
	{ (float)0.189878,	34,	323 },
	{ (float)0.186216,	36,	357 },
	{ (float)0.186216,	36,	393 },
	{ (float)0.182592,	38,	429 },
	{ (float)0.179003,	40,	467 },
	{ (float)0.175466,	42,	507 },
	{ (float)0.172001,	44,	549 },
	{ (float)0.172001,	44,	593 },
	{ (float)0.168612,	46,	637 },
	{ (float)0.168612,	46,	683 },
	{ (float)0.163575,	49,	729 },
	{ (float)0.158642,	52,	778 },
	{ (float)0.158642,	52,	830 },
	{ (float)0.158642,	52,	882 },
	{ (float)0.153815,	55,	934 },
	{ (float)0.153815,	55,	989 },
	{ (float)0.149097,	58,	1044 },
	{ (float)0.149097,	58,	1102 },
	{ (float)0.142746,	62,	1160 },
	{ (float)0.142746,	62,	1222 },
	{ (float)0.142746,	62,	1284 },
	{ (float)0.138270,	65,	1346 },
	{ (float)0.138270,	65,	1411 },
	{ (float)0.138270,	65,	1476 },
	{ (float)0.132166,	69,	1541 },
	{ (float)0.132166,	69,	1610 },
	{ (float)0.126204,	73,	1679 },
	{ (float)0.126204,	73,	1752 },
	{ (float)0.126204,	73,	1825 },
	{ (float)0.120381,	77,	1898 },
	{ (float)0.120381,	77,	1975 },
	{ (float)0.120381,	77,	2052 },
	{ (float)0.120381,	77,	2129 },
	{ (float)0.112962,	82,	2206 },
	{ (float)0.112962,	82,	2288 },
	{ (float)0.112962,	82,	2370 },
	{ (float)0.107450,	86,	2452 },
	{ (float)0.107450,	86,	2538 },
	{ (float)0.107450,	86,	2624 },
	{ (float)0.107450,	86,	2710 },
	{ (float)0.100343,	91,	2796 },
	{ (float)0.100343,	91,	2887 },
	{ (float)0.100343,	91,	2978 },
	{ (float)0.095126,	95,	3069 },
	{ (float)0.095126,	95,	3164 },
	{ (float)0.095126,	95,	3259 },
	{ (float)0.095126,	95,	3354 },
	{ (float)0.088276,	100,	3449 },
	{ (float)0.088276,	100,	3549 },
	{ (float)0.088276,	100,	3649 },
	{ (float)0.088276,	100,	3749 },
	{ (float)0.081523,	105,	3849 },
	{ (float)0.081523,	105,	3954 },
	{ (float)0.081523,	105,	4059 },
	{ (float)0.081523,	105,	4164 },
	{ (float)0.074861,	110,	4269 },
	{ (float)0.074861,	110,	4379 },
	{ (float)0.074861,	110,	4489 },
	{ (float)0.074861,	110,	4599 },
	{ (float)0.068290,	115,	4709 },
	{ (float)0.068290,	115,	4824 },
	{ (float)0.068290,	115,	4939 },
	{ (float)0.068290,	115,	5054 },
	{ (float)0.063573,	119,	5169 },
	{ (float)0.063573,	119,	5288 },
	{ (float)0.063573,	119,	5407 },
	{ (float)0.063573,	119,	5526 },
	{ (float)0.057219,	124,	5645 },
	{ (float)0.057219,	124,	5769 },
	{ (float)0.057219,	124,	5893 },
	{ (float)0.057219,	124,	6017 },
	{ (float)0.050985,	129,	6141 },
	{ (float)0.050985,	129,	6270 },
	{ (float)0.050985,	129,	6399 },
	{ (float)0.050985,	129,	6528 },
	{ (float)0.050985,	129,	6657 },
	{ (float)0.044859,	134,	6786 },
	{ (float)0.044859,	134,	6920 },
	{ (float)0.044859,	134,	7054 },
	{ (float)0.044859,	134,	7188 },
	{ (float)0.040571,	138,	7322 },
	{ (float)0.040571,	138,	7460 },
	{ (float)0.040571,	138,	7598 },
	{ (float)0.040571,	138,	7736 },
	{ (float)0.036339,	142,	7874 },
	{ (float)0.036339,	142,	8016 },
	{ (float)0.036339,	142,	8158 },
	{ (float)0.036339,	142,	8300 },
	{ (float)0.032139,	146,	8442 },
	{ (float)0.032139,	146,	8588 },
	{ (float)0.032139,	146,	8734 },
	{ (float)0.032139,	146,	8880 },
	{ (float)0.027947,	150,	9026 },
	{ (float)0.027947,	150,	9176 },
	{ (float)0.027947,	150,	9326 },
	{ (float)0.023739,	154,	9476 },
	{ (float)0.023739,	154,	9630 },
	{ (float)0.023739,	154,	9784 },
	{ (float)0.023739,	154,	9938 },
	{ (float)0.019504,	158,	10092 },
	{ (float)0.019504,	158,	10250 },
	{ (float)0.019504,	158,	10408 },
	{ (float)0.016976,	161,	10566 },
	{ (float)0.016976,	161,	10727 },
	{ (float)0.016976,	161,	10888 },
	{ (float)0.016976,	161,	11049 },
	{ (float)0.012639,	165,	11210 },
	{ (float)0.012639,	165,	11375 },
	{ (float)0.012639,	165,	11540 },
	{ (float)0.009991,	168,	11705 },
	{ (float)0.009991,	168,	11873 },
	{ (float)0.009991,	168,	12041 },
	{ (float)0.009016,	170,	12209 },
	{ (float)0.009016,	170,	12379 },
	{ (float)0.009016,	170,	12549 },
	{ (float)0.006217,	173,	12719 },
	{ (float)0.006217,	173,	12892 },
	{ (float)0.005097,	175,	13065 },
	{ (float)0.005097,	175,	13240 },
	{ (float)0.005097,	175,	13415 },
	{ (float)0.003909,	177,	13590 },
	{ (float)0.003909,	177,	13767 },
	{ (float)0.002340,	177,	13944 },
	{ (float)0.002389,	170,	14121 },
	{ (float)0.001068,	164,	14291 },
	{ (float)0.001653,	157,	14455 },
	{ (float)0.000717,	150,	14612 },
	{ (float)0.001614,	143,	14762 },
	{ (float)0.000270,	136,	14905 },
	{ (float)0.000484,	129,	15041 },
	{ (float)0.001103,	123,	15170 },
	{ (float)0.001242,	115,	15293 },
	{ (float)0.001188,	109,	15408 },
	{ (float)0.001011,	103,	15517 },
	{ (float)0.000709,	97,	15620 },
	{ (float)0.000301,	89,	15717 },
	{ (float)0.002416,	82,	15806 },
	{ (float)0.003251,	76,	15888 },
	{ (float)0.003246,	69,	15964 },
	{ (float)0.004141,	62,	16033 },
	{ (float)0.005963,	55,	16095 },
	{ (float)0.008839,	47,	16150 },
	{ (float)0.010490,	40,	16197 },
	{ (float)0.016994,	31,	16237 },
	{ (float)0.023659,	21,	16268 },
};

/// @}
