/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/
/*=======================================================================
* Description : Shader library for volume rendering
*========================================================================*/

//NVIDIA's bug workaround: if(x)...else...
//on an uniform sometimes doesn't work so use 0,1 and a lerp
uniform float VVizNoTexGen;

uniform bool VVizUseOrthoCamera;

uniform float VVizDoMultiVolume;
uniform mat4 VVizMVI;

uniform float VVizSliceSpacing;
uniform float VVizGenVertices;

uniform vec3 VVizTileMaxIJK;
uniform vec3 VVizTileMinIJK;
uniform vec3 VVizVolumeDimensions;
uniform vec3 VVizVolumeExtend;
varying vec3 VVizLightingVec;
varying vec3 VVizViewVec;
varying vec4 VVizHalfVec;

//NVidia BUG: Reading varying can lead to
//an internal compiler error so do a tmp copy of varyings
vec3 VVizTmpLight, VVizTmpHalf, VVizTmpView;

uniform vec3 VVizScaleFactor;

//Generated vertex
vec4 VVizVertex;

uniform vec3 VVizZAxis;

uniform vec2 VVizMinMaxViewSpaceZ;

vec4 VVizGenerateVertexInternal();
void OivSetupShadowVertex(vec4 vertex);

/**
 * Set VVizVertex to gl_Vertex for compatibility with OIV6
 * Must be called by all OIV6 functions using VVizVertex
 */
void VVizOIV6VertexCompatibility()
{
  if ( VVizGenVertices != 1.0 )
    VVizVertex = gl_Vertex;
}

/**
 * Generate slice on GPU
 */
vec4 VVizGenerateVertex()
{
  VVizVertex = VVizGenerateVertexInternal();
  OivSetupShadowVertex(VVizVertex);

  //Put normalized view space Z into VVizHalfVec.w
  VVizHalfVec.w = (gl_ModelViewMatrix*VVizVertex).z;
  VVizHalfVec.w = (VVizHalfVec.w-VVizMinMaxViewSpaceZ.x)/(VVizMinMaxViewSpaceZ.y-VVizMinMaxViewSpaceZ.x);

  return VVizVertex;
}

// Computes "object linear" texture coordinates using planes defined by VolumeViz.
// Texture coordinates computed are relative to the current tile.
vec3 VVizTexGen(vec4 vert)
{
  vec3 res;
  res.x = dot(gl_ObjectPlaneS[0], vert);
  res.y = dot(gl_ObjectPlaneT[0], vert);
  res.z = dot(gl_ObjectPlaneR[0], vert);

  return res;
}

// Computes "object linear" texture coordinates using planes defined by VolumeViz.
// Texture coordinates computed are relative to the entire volume.
vec3 VVizTexGenVol(vec4 vert)
{
  vec3 res;
  res.x = dot(gl_ObjectPlaneS[1], vert);
  res.y = dot(gl_ObjectPlaneT[1], vert);
  res.z = dot(gl_ObjectPlaneR[1], vert);

  return res;
}

vec3 VVizComputeViewDir()
{
  VVizOIV6VertexCompatibility();

  vec3 eye = (gl_ModelViewMatrixInverse*vec4(0, 0, 0, 1)).xyz;
  // not normalized because norm is not used. (see VVizComputeBackSliceTexCoord)
  return eye.xyz-VVizVertex.xyz;
}

void VVizComputeBackSliceTexCoordPerspective()
{
  VVizOIV6VertexCompatibility();

  vec3 view = VVizComputeViewDir();

  //NVDIA's bug: if this dot product is directly computed in the backVert
  //expression, compilation failed after switching shader 2 times
  float zAxisDotView = dot(VVizZAxis, view);

  // Back slice
  vec4 backVert = vec4(VVizVertex.xyz+view*(VVizSliceSpacing/zAxisDotView), 1);
  gl_TexCoord[1].xyz = VVizNoTexGen*gl_MultiTexCoord1.xyz+
                       (1.-VVizNoTexGen)*VVizTexGen(backVert);
}

void VVizComputeBackSliceTexCoordOrtho()
{
  VVizOIV6VertexCompatibility();

  // ortho case is view = -zaxis
  vec3 view = -VVizZAxis/(VVizScaleFactor*VVizScaleFactor);

  float zAxisDotView = dot(VVizZAxis, view);

  // Back slice
  vec4 backVert = vec4(VVizVertex.xyz+view*(VVizSliceSpacing/zAxisDotView), 1);
  gl_TexCoord[1].xyz = VVizNoTexGen*gl_MultiTexCoord1.xyz+
                       (1.-VVizNoTexGen)*VVizTexGen(backVert);
}

void VVizComputeBackSliceTexCoord()
{
  if ( VVizUseOrthoCamera )
    VVizComputeBackSliceTexCoordOrtho();
  else
    VVizComputeBackSliceTexCoordPerspective();
}

void VVizComputeFrontSliceTexCoord()
{
  VVizOIV6VertexCompatibility();

  //Front slice
  //Bug workaround: when using a if(VVizNoTexGen==1)...else...
  //it is impossible to retrieve the uniform location.
  gl_TexCoord[0] = VVizNoTexGen*gl_MultiTexCoord0+
                   vec4((1.-VVizNoTexGen)*VVizTexGen(VVizVertex), 0.);
}

//Compute lighting vector when multivolume is off.
void VVizComputeLightingVectorsNoMultiVolume()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(gl_ModelViewMatrixInverse[0].xyz,
                  gl_ModelViewMatrixInverse[1].xyz,
                  gl_ModelViewMatrixInverse[2].xyz);
  vec3 tmpLight = mvi*gl_LightSource[0].position.xyz;
  tmpLight = normalize(tmpLight);

  vec4 eye = gl_ModelViewMatrixInverse*vec4(0, 0, 0, 1);
  vec3 tmpView = eye.xyz-VVizVertex.xyz;
  vec3 tmpHalf = normalize(tmpView+tmpLight);

  VVizTmpLight = mix(tmpLight, VVizTmpLight, VVizDoMultiVolume);
  VVizTmpView = mix(tmpView, VVizTmpView, VVizDoMultiVolume);  //VVizTmpView;
  VVizTmpHalf = mix(tmpHalf, VVizTmpHalf, VVizDoMultiVolume); //VVizTmpHalf;
}

//Compute lighting vector when multivolume is on.
//Vertices are in view space and must be transformed back to object space
void VVizComputeLightingVectorsMultiVolume()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(VVizMVI[0].xyz,
                  VVizMVI[1].xyz,
                  VVizMVI[2].xyz);
  vec3 tmpLight = mvi*gl_LightSource[0].position.xyz;
  tmpLight = normalize(tmpLight);

  vec4 eye = VVizMVI*vec4(0, 0, 0, 1);
  vec3 tmpView =  eye.xyz-(VVizMVI*VVizVertex).xyz;
  vec3 tmpHalf = normalize(tmpView+tmpLight);

  VVizTmpLight = mix(tmpLight, VVizTmpLight, 1.-VVizDoMultiVolume);
  VVizTmpView = mix(tmpView, VVizTmpView, 1.-VVizDoMultiVolume);  //VVizTmpView;
  VVizTmpHalf = mix(tmpHalf, VVizTmpHalf, 1.-VVizDoMultiVolume); //VVizTmpHalf;
}

void VVizComputeLightingVectorsPerspective()
{
  VVizOIV6VertexCompatibility();

  VVizTmpLight = vec3(0, 0, 0);
  VVizTmpView = vec3(0, 0, 0);
  VVizTmpHalf = vec3(0, 0, 0);

  VVizComputeLightingVectorsNoMultiVolume();
  VVizComputeLightingVectorsMultiVolume();

  VVizLightingVec = VVizTmpLight*VVizScaleFactor;
  VVizViewVec = VVizTmpView*VVizScaleFactor;
  VVizHalfVec.xyz = VVizTmpHalf*VVizScaleFactor;
}

//Compute lighting vector when multivolume is off.
void VVizComputeLightingVectorsOrthoNoMultiVolume()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(gl_ModelViewMatrixInverse[0].xyz,
                  gl_ModelViewMatrixInverse[1].xyz,
                  gl_ModelViewMatrixInverse[2].xyz);
  VVizTmpLight = mvi*gl_LightSource[0].position.xyz;
  VVizTmpLight = normalize(VVizTmpLight);

  VVizTmpView =  (gl_ModelViewMatrixInverse*vec4(0, 0, 1, 0)).xyz;
  VVizTmpHalf = normalize(VVizTmpView+VVizTmpLight);

  VVizViewVec = VVizTmpView;
  VVizHalfVec.xyz = VVizTmpHalf;
  VVizLightingVec = VVizTmpLight;
}

//Compute lighting vector when multivolume is on.
//Vertices are in view space and must be transformed back to object space
void VVizComputeLightingVectorsOrthoMultiVolume()
{
  //Do Objectspace lighting
  mat3 mvi = mat3(VVizMVI[0].xyz,
                  VVizMVI[1].xyz,
                  VVizMVI[2].xyz);
  VVizTmpLight = mvi*gl_LightSource[0].position.xyz;
  VVizTmpLight = normalize(VVizTmpLight);

  VVizTmpView =  (VVizMVI*vec4(0, 0, 1, 0)).xyz;
  VVizTmpHalf = normalize(VVizTmpView+VVizTmpLight);

  VVizViewVec = VVizTmpView;
  VVizHalfVec.xyz = VVizTmpHalf;
  VVizLightingVec = VVizTmpLight;
}

void VVizComputeLightingVectorsOrtho()
{
  VVizOIV6VertexCompatibility();

  if(VVizDoMultiVolume == 0.) {
    VVizComputeLightingVectorsOrthoNoMultiVolume();
  } else {
    VVizComputeLightingVectorsOrthoMultiVolume();
  }
}

void VVizComputeLightingVectors()
{
  if ( VVizUseOrthoCamera )
    VVizComputeLightingVectorsOrtho();
  else
    VVizComputeLightingVectorsPerspective();
}
