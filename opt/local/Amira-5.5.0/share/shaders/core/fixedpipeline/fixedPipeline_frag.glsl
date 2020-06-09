#define ENV_MODE_MODULATE 0
#define ENV_MODE_REPLACE 1
#define ENV_MODE_DECAL 2
#define ENV_MODE_BLEND 3
#define ENV_MODE_ADD 4
#define ENV_MODE_NONE 5

uniform sampler2D OivTexture;
uniform int OivTexEnvMode = ENV_MODE_MODULATE;
uniform bool OivTexturing = false;

float OivComputeShadow();

void main()
{
  vec4 frag = gl_Color;
  if ( OivTexturing )
  {
    vec4 tex = texture2D(OivTexture, gl_TexCoord[0].xy);
    if ( OivTexEnvMode == ENV_MODE_MODULATE )
      frag = tex*frag;
    else if ( OivTexEnvMode == ENV_MODE_REPLACE )
      frag.xyz = tex.xyz;
    else if ( OivTexEnvMode == ENV_MODE_DECAL )
      frag.xyz = frag.xyz*(1.-tex.w)+tex.xyz*tex.w;
    else if ( OivTexEnvMode == ENV_MODE_BLEND )
    {
      frag.xyz = frag.xyz*(1.-tex.w)+tex.xyz*frag.xyz;
      frag.w = frag.w*tex.w;
    }
    else if ( OivTexEnvMode == ENV_MODE_ADD )
    {
      frag.xyz = frag.xyz+tex.xyz;
      frag.w = frag.w*tex.w;
    }
  }

  float shadow = OivComputeShadow();
  gl_FragColor.xyz = frag.xyz*shadow;
  gl_FragColor.w = frag.w;
}
