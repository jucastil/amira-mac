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

/// @addtogroup hxfieldcompat hxfieldcompat
/// @{
#ifndef __QUADSUPERSPLINES_H
#define __QUADSUPERSPLINES_H
#include <mclib/McMat3f.h>
#include "HxFieldCompatWinDLLApi.h"
class HXFIELDCOMPAT_API BitsToTetras {
  short int map[2][2][2][2][2][2];
  short int tetraPoints[24][3];
  short int E[24][6];
  short int mapToA[24][3][3][3][3];
  float points[14][3];

protected:
  McMat3f alpha[24];
public:
  BitsToTetras ();
  inline const McMat3f & getAlpha(short int t) const {
    return alpha[t];
  }
  inline short int  operator () (short int t, short int i, short int j, short int k, short int l) const {
    return mapToA[t][i][j][k][l];
  } 
  inline /*static*/ short int P0(const float *X) const {
    return (X[0]+X[1])>=0?1:0;
  }
  inline /*static*/ short int P1(const float *X) const {
    return (X[0]-X[1])>=0?1:0;
  }
  inline /*static*/ short int P2(const float *X) const {
    return (X[0]+X[2])>=0?1:0;
  }
  inline /*static*/ short int P3(const float *X) const {
    return (X[0]-X[2])>=0?1:0;
  }
  inline /*static*/ short int P4(const float *X) const {
    return (X[1]+X[2])>=0?1:0;
  }
  inline /*static*/ short int P5(const float *X) const {
    return (X[1]-X[2])>=0?1:0;
  }
  inline short int mapPointToTetra(const float *X) const {
    return map[P0(X)][ P1(X)][ P2(X)][ P3(X)][ P4(X)][ P5(X)];
  }
  /// X has 6 coordinates: itself in the first three, -itself in the last three coordinates;
  inline void bary(short int t, const float*X, float*bc) const {
    
        bc[0]=1+X[E[t][0]]+X[E[t][1]];
        bc[1]=X[E[t][2]]+X[E[t][3]];
        bc[2]=X[E[t][4]]+X[E[t][5]];
        bc[3]=1-bc[0]-bc[1]-bc[2];
  }
  inline void euclid(short int t, float * X, float*bc) const {
    X[0]=X[1]=X[2]=0.0;
    for (int p=1; p < 4; p ++) {
      for (int j=0; j < 3; j++) {
        X[j]+=bc[p]*points[tetraPoints[t][p-1]][j];
      }
    }
  }
  friend class QuadSuperSpline;
};
class HXFIELDCOMPAT_API QuadSuperSpline {
private:
  int NDataVar;
  float *a;//a[65];
  //         z  y  x
  float *Data;//[3][3][3];
  float * a1000, * a0100, * a0010, * a0001;
  float * delzeta;
  float * hesszeta;
public:
  float jacFactor[3];
  static const BitsToTetras bitsToTetras;
  QuadSuperSpline(){Data=0;NDataVar=0;jacFactor[0]=jacFactor[1]=jacFactor[2]=1.0;};
  ~QuadSuperSpline(){if (Data) {delete Data;delete a;delete a1000;delete delzeta;}};
  /// Constructor taking 9 lattice data values with current cube centered - x runs fastest, y, z.
  QuadSuperSpline(int anDataVar);
  QuadSuperSpline(int anDataVar, float * adata);
  int inline nDataVar() {return NDataVar;}
  inline void updateMem(int anDataVar) {

    if (anDataVar!=NDataVar) {
      NDataVar=anDataVar;
      if (Data) {
        delete Data;
        delete a;
        delete a1000;
        delete delzeta;
        delete hesszeta;
      }
      a= new float [65*NDataVar];
      Data= new float [27*NDataVar];
      a1000=new float[4*NDataVar];
      a0100=&a1000[NDataVar];
      a0010=&a0100[NDataVar];
      a0001=&a0010[NDataVar];

      delzeta=new float[3*NDataVar];
      hesszeta=new float[9*NDataVar];
    }
  }
  void setA();
  void setA(int anDataVar, float * adata);
  inline void setA(float * adata) {
    setA(1,adata);
  }
  enum {
    AV=0
    ,AF=8
    ,AVQ=14
    ,AE=15
    ,AC=27
    ,AM=35
    ,AG=59
  };
  inline float* data(const int x, const int y, const int z) {
    return &Data[NDataVar*(9*(z+1)+3*(y+1)+x+1)];
  }
  inline float* av(const unsigned short i){
    return &a[NDataVar*i];
  }
  inline float * ae(const unsigned short i){
    return &a[NDataVar*(i+AE)];
  }
  inline float * af(const unsigned short i){
    return &a[NDataVar*(i+AF)];
  }
  inline float * ac(const unsigned short i){
    return &a[NDataVar*(i+AC)];
  }
  inline float * am(const unsigned short i){
    return &a[NDataVar*(i+AM)];
  }
  inline float * ag(const unsigned short i){
    return &a[NDataVar*(i+AG)];
  }
  inline float * avQ(){
    return &a[NDataVar*(AVQ)];
  }
  void deCasteljau(float * v, short int t, float *bc);
  inline void deCasteljau(float * v, float *X) {
    int t=bitsToTetras.mapPointToTetra(X);
    float bc[4];
    bitsToTetras.bary(t, X, bc);
    deCasteljau(v, t, bc);
  }
  void jacobian(float * jac, short int t, float *bc);
  inline void jacobian(float * jac, float *X) {
    int t=bitsToTetras.mapPointToTetra(X);
    float bc[4];
    bitsToTetras.bary(t, X, bc);
    jacobian(jac, t, bc);
  }
  void hessian(float*hess, short int t);
  inline void hessian(float * hess, float *X) {
    hessian(hess, bitsToTetras.mapPointToTetra(X));
  }


};
#endif

/// @}
