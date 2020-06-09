/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/
/*=======================================================================
* Description : Volume clipping
*========================================================================*/

uniform float VVizClipOutside;
uniform vec3 VVizOneOverDepthTexSize;
uniform vec3 VVizLowResolutionScale;

uniform sampler2D VVizDepthTex0;
uniform sampler2D VVizDepthTex1;
uniform sampler2D VVizDepthTex2;
uniform sampler2D VVizDepthTex3;
uniform sampler2D VVizDepthTex4;
uniform sampler2D VVizDepthTex5;
uniform sampler2D VVizDepthTex6;
uniform sampler2D VVizDepthTex7;
uniform sampler2D VVizDepthTex8;
uniform sampler2D VVizDepthTex9;

void VVizClipVolumeGrid()
{
  vec3 texCoord = gl_FragCoord.xyz*VVizOneOverDepthTexSize*VVizLowResolutionScale;

  bool pass = (texture2D(VVizDepthTex0, texCoord.xy).w <= texCoord.z &&
               texture2D(VVizDepthTex1, texCoord.xy).w > texCoord.z) ||
              (texture2D(VVizDepthTex2, texCoord.xy).w <= texCoord.z &&
               texture2D(VVizDepthTex3, texCoord.xy).w > texCoord.z) ||
              (texture2D(VVizDepthTex4, texCoord.xy).w <= texCoord.z &&
               texture2D(VVizDepthTex5, texCoord.xy).w > texCoord.z) ||
              (texture2D(VVizDepthTex6, texCoord.xy).w <= texCoord.z &&
               texture2D(VVizDepthTex7, texCoord.xy).w > texCoord.z) ||
              (texture2D(VVizDepthTex8, texCoord.xy).w <= texCoord.z &&
               texture2D(VVizDepthTex9, texCoord.xy).w > texCoord.z);

  // fix driver bug in MAC. Original code is
  // if((pass && VVizClipOutside == 0.0) || (!pass && VVizClipOutside == 1.0))
  //   discard;
  bool mustDiscard = (pass && VVizClipOutside == 0.0) || (!pass && VVizClipOutside == 1.0);
  if( !mustDiscard )
  {
    // NOTHING
  }
  else
  {
    discard;
  }

}
