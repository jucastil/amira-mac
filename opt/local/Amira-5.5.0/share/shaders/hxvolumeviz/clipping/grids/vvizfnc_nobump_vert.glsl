/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/
/*=======================================================================
* Description : Shader library for volume rendering when using uniform grid
*               clipping (allow to spare 2 varyings)
*========================================================================*/

//NVIDIA's bug workaround: if(x)...else...
//on an uniform sometimes doesn't work so use 0,1 and a lerp
uniform float VVizNoTexGen;
uniform float VVizDoMultiVolume;

uniform mat4 VVizMVI;

uniform float VVizSliceSpacing;
varying vec3 VVizLightingVec;
varying vec3 VVizViewVec;
varying vec4 VVizHalfVec;

//NVidia BUG: Reading varying can lead to
//an internal compiler error so do a tmp copy of varyings
vec3 VVizTmpLight, VVizTmpHalf, VVizTmpView;

vec3 VVizTexGen(vec4 vert)
{
  vec3 res;
  res.x = dot(gl_ObjectPlaneS[0], vert);
  res.y = dot(gl_ObjectPlaneT[0], vert);
  res.z = dot(gl_ObjectPlaneR[0], vert);

  return res;
}

void VVizComputeBackSliceTexCoord()
{
  vec4 eye = gl_ModelViewMatrixInverse*vec4(0, 0, 0, 1);
  vec3 view = normalize(eye.xyz-gl_Vertex.xyz);
  // compute view direction
  vec4 vDir = normalize(gl_ModelViewMatrixInverse*vec4(0, 0, -1, 0));

  //NVDIA's bug: if this dot product is directly computed in the backVert
  //expression, compilation failed after switching shader 2 times
  float vDirDotView = dot(vDir.xyz,view);
  // Back slice
  vec4 backVert = vec4(gl_Vertex.xyz+view*(VVizSliceSpacing/vDirDotView), 1);
  gl_TexCoord[1].xyz = VVizTexGen(backVert);

}

void VVizComputeBackSliceTexCoordOrtho()
{
  // compute view direction
  vec4 vDir = normalize(gl_ModelViewMatrixInverse*vec4(0, 0, -1, 1));

  // Back slice
  vec4 backVert = vec4(gl_Vertex.xyz+vDir.xyz*VVizSliceSpacing, 1);
  gl_TexCoord[1].xyz = VVizTexGen(backVert);
}

void VVizComputeFrontSliceTexCoord()
{
  //Front slice
  //Bug workaround: when using a if(VVizNoTexGen==1)...else...
  //it is impossible to retrieve the uniform location.
  gl_TexCoord[0].xyz = VVizNoTexGen*gl_MultiTexCoord0.xyz+
                       (1.-VVizNoTexGen)*VVizTexGen(gl_Vertex);
}

//Compute lighting vector when multivolume is off.
void VVizComputeLightingVectorsNoMv()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(gl_ModelViewMatrixInverse[0].xyz,
                  gl_ModelViewMatrixInverse[1].xyz,
                  gl_ModelViewMatrixInverse[2].xyz);
  vec3 tmpLight = mvi*gl_LightSource[0].position.xyz;
  tmpLight = normalize(tmpLight);

  vec4 eye = gl_ModelViewMatrixInverse*vec4(0, 0, 0, 1);
  vec3 tmpView =  normalize(eye.xyz-gl_Vertex.xyz);
  vec3 tmpHalf = normalize(tmpView+tmpLight);

  VVizTmpLight = mix(tmpLight, VVizTmpLight, VVizDoMultiVolume);
  VVizTmpView = mix(tmpView, VVizTmpView, VVizDoMultiVolume);  //VVizTmpView;
  VVizTmpHalf = mix(tmpHalf, VVizTmpHalf, VVizDoMultiVolume); //VVizTmpHalf;
}

//Compute lighting vector when multivolume is on.
//Vertices are in view space and must be transformed back to object space
void VVizComputeLightingVectorsMV()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(VVizMVI[0].xyz,
                  VVizMVI[1].xyz,
                  VVizMVI[2].xyz);
  vec3 tmpLight = mvi*gl_LightSource[0].position.xyz;
  tmpLight = normalize(tmpLight);

  vec4 eye = VVizMVI*vec4(0, 0, 0, 1);
  vec3 tmpView =  normalize(eye.xyz-(VVizMVI*gl_Vertex).xyz);
  vec3 tmpHalf = normalize(tmpView+tmpLight);

  VVizTmpLight = mix(tmpLight, VVizTmpLight, 1.-VVizDoMultiVolume);
  VVizTmpView = mix(tmpView, VVizTmpView, 1.-VVizDoMultiVolume);  //VVizTmpView;
  VVizTmpHalf = mix(tmpHalf, VVizTmpHalf, 1.-VVizDoMultiVolume); //VVizTmpHalf;
}

void VVizComputeLightingVectors()
{
  VVizTmpLight = vec3(0, 0, 0);
  VVizTmpView = vec3(0, 0, 0);
  VVizTmpHalf = vec3(0, 0, 0);

  VVizComputeLightingVectorsNoMv();
  VVizComputeLightingVectorsMV();

  VVizLightingVec = VVizTmpLight;
  VVizViewVec = VVizTmpView;
  VVizHalfVec.xyz = VVizTmpHalf;
}

//Compute lighting vector when multivolume is off.
void VVizComputeLightingVectorsOrthoNoMV()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(gl_ModelViewMatrixInverse[0].xyz,
                  gl_ModelViewMatrixInverse[1].xyz,
                  gl_ModelViewMatrixInverse[2].xyz);
  VVizTmpLight = mvi*gl_LightSource[0].position.xyz;
  VVizTmpLight = normalize(VVizTmpLight);

  VVizTmpView =  normalize(gl_ModelViewMatrixInverse*vec4(0, 0, -1, 1)).xyz;
  VVizTmpHalf = normalize(VVizTmpView+VVizTmpLight);

  VVizViewVec = VVizTmpView;
  VVizHalfVec.xyz = VVizTmpHalf;
  VVizLightingVec = VVizTmpLight;
}

//Compute lighting vector when multivolume is on.
//Vertices are in view space and must be transformed back to object space
void VVizComputeLightingVectorsOrthoMV()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(VVizMVI[0].xyz,
                  VVizMVI[1].xyz,
                  VVizMVI[2].xyz);
  VVizTmpLight = mvi*gl_LightSource[0].position.xyz;
  VVizTmpLight = normalize(VVizTmpLight);

  VVizTmpView =  normalize(VVizMVI*vec4(0, 0, -1, 0)).xyz;
  VVizTmpHalf = normalize(VVizTmpView+VVizTmpLight);

  VVizViewVec = VVizTmpView;
  VVizHalfVec.xyz = VVizTmpHalf;
  VVizLightingVec = VVizTmpLight;
}

void VVizComputeLightingVectorsOrtho()
{
  if(VVizDoMultiVolume == 0.) {
    VVizComputeLightingVectorsOrthoNoMV();
  } else {
    VVizComputeLightingVectorsOrthoMV();
  }
}

void VVizComputeTangentSpaceLightingVectors()
{
}
