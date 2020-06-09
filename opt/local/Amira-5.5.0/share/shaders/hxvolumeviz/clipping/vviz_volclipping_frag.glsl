/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
** Modified    : David BEILLOIN (Mar 2011)
**=======================================================================*/
/*=======================================================================
* Description : Volume clipping
*========================================================================*/
#extension GL_EXT_texture_array : enable
uniform sampler2DArray VVizDepthTex;

uniform float VVizClipOutside;
uniform vec3 VVizOneOverDepthTexSize;
uniform vec3 VVizLowResolutionScale;
uniform float VVizNumLayers;
uniform float VVizNumPass;

void VVizClipVolumeGrid()
{
  vec3 texCoord = gl_FragCoord.xyz*VVizOneOverDepthTexSize*VVizLowResolutionScale;
  bool pass = false;
  
  float idxStart = 0.0;
  // manage case where we are inside
  if ( mod( VVizNumPass,2) !=0)
  {
    float val1 = texture2DArrayLod(VVizDepthTex, vec3(texCoord.xy,idxStart),0).x;
    pass = pass || (val1 > texCoord.z) ;

    if( pass && VVizClipOutside == 0.0 )
      discard;
    idxStart=1.0;      
  }
  
  for (float idx=idxStart; idx <VVizNumPass; idx+=2.0)
  {
    float val0 = texture2DArrayLod(VVizDepthTex, vec3(texCoord.xy,idx  ),0).x;
    float val1 = texture2DArrayLod(VVizDepthTex, vec3(texCoord.xy,idx+1.),0).x;
    pass = pass || ((val0 <= texCoord.z) && (val1 > texCoord.z)) ;
  
    if( pass && VVizClipOutside == 0.0 )
      discard;
  }
  if(!pass && VVizClipOutside == 1.0)
    discard;
}
