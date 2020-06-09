uniform sampler2D colorTex;
uniform sampler2D distanceTex;
uniform vec2 texSizeInv;

uniform float innerEdgeThreshold;
uniform float outterEdgeThreshold;
uniform vec3 edgeColor;

uniform bool useDepth;
uniform bool useLuminance;
uniform bool useGradient;

//#define DEBUGIZIL
//#define DEBUGIN
//#define DEBUGIZ
//#define DEBUGIL
//#define DEBUGSHOWCOL
//#define DEBUGIZINIL
//#define DEBUGSHOWDEPTH
//#define DEBUGSHOWGRAD


float getLuminance(vec4 c)
{
  vec3 rgb2l = vec3(0.3, 0.59, 0.11);
  return dot(rgb2l, c.xyz);
}

mat3 getNeighborsZBuffer()
{
  vec4 offs = vec4(texSizeInv, -texSizeInv);
  float scale = 1.;
  float z00 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.zw).x*scale;
  float z10 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(0., offs.w)).x*scale;
  float z20 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.xw).x*scale;

  float z01 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(offs.z, 0.)).x*scale;
  float z11 = texture2D(distanceTex, gl_TexCoord[0].xy).x*scale;
  float z21 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(offs.x, 0.)).x*scale;

  float z02 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.zy).x*scale;
  float z12 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(0., offs.y)).x*scale;
  float z22 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.xy).x*scale;

  return mat3(z00, z01, z02,
              z10, z11, z12,
              z20, z21, z22);
}

mat3 getNeighborsLum()
{
  vec4 offs = vec4(texSizeInv, -texSizeInv);
  float z00 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+offs.zw));
  float z10 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+vec2(0., offs.w)));
  float z20 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+offs.xw));

  float z01 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+vec2(offs.z, 0.)));
  float z11 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy));
  float z21 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+vec2(offs.x, 0.)));

  float z02 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+offs.zy));
  float z12 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+vec2(0., offs.y)));
  float z22 = getLuminance(texture2D(colorTex, gl_TexCoord[0].xy+offs.xy));

  return mat3(z00, z01, z02,
              z10, z11, z12,
              z20, z21, z22);
}

mat3 getNeighborsGrad()
{
  vec4 offs = vec4(texSizeInv, -texSizeInv);
  float z00 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.zw).y;
  float z10 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(0., offs.w)).y;
  float z20 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.xw).y;

  float z01 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(offs.z, 0.)).y;
  float z11 = texture2D(distanceTex, gl_TexCoord[0].xy).y;
  float z21 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(offs.x, 0.)).y;

  float z02 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.zy).y;
  float z12 = texture2D(distanceTex, gl_TexCoord[0].xy+vec2(0., offs.y)).y;
  float z22 = texture2D(distanceTex, gl_TexCoord[0].xy+offs.xy).y;

  return mat3(z00, z01, z02,
              z10, z11, z12,
              z20, z21, z22);
}

float sobel(mat3 data)
{
  vec4 offs = vec4(texSizeInv, -texSizeInv);

  mat3 gxKern = mat3(-1., -2., -1.,
                     0., 0., 0.,
                     1., 2., 1.);
  mat3 gyKern = mat3(-1., 0., 1.,
                     -2., 0., 2.,
                     -1., 0., 1.);

  float gx = dot(data[0], gxKern[0])+
             dot(data[1], gxKern[1])+
             dot(data[2], gxKern[2]);

  float gy = dot(data[0], gyKern[0])+
             dot(data[1], gyKern[1])+
             dot(data[2], gyKern[2]);

  return sqrt(gx*gx+gy*gy);
}

float computeIn()
{
  if ( useGradient )
  {
    float In = sobel(getNeighborsGrad());
    In = 1.-clamp(In, 0., 1.);
    In = In >= (1.-innerEdgeThreshold)?1.:In;
    return In;
  }
  else
  {
    return 1.;
  }
}

float computeIz()
{
  if ( !useDepth )
    return 1.;

  float Iz = sobel(getNeighborsZBuffer());
  Iz = 1.-clamp(Iz, 0., 1.);
  Iz = Iz >= (1.-outterEdgeThreshold)?1.:Iz;

  return Iz;
}

float computeIl()
{
  if ( !useLuminance )
    return 1.;

  float Il = sobel(getNeighborsLum());
  Il = 1.-clamp(Il, 0., 1.);

  return Il;
}

void main()
{
  vec4 col = texture2D(colorTex, gl_TexCoord[0].xy);

  //Use gradients info for outter edges
  float In = computeIn();

  //Use depth infos for inner edges
  float Iz = computeIz();

  //Use lumincance
  float Il = computeIl();

  vec4 finalEdgeColor = vec4(edgeColor, col.w);
  col = mix(finalEdgeColor, col, In*Iz*Il);
  //col = mix(finalEdgeColor, col, Iz*Il);
  //col = mix(finalEdgeColor, col, In);
   gl_FragColor = col;

#ifdef DEBUGIN
   gl_FragColor = vec4(In, In, In, 1.0);
#endif

#ifdef DEBUGIL
   gl_FragColor = vec4(Il, Il, Il, 1.0);
#endif

#ifdef DEBUGIZ
  gl_FragColor = vec4(Iz, Iz, Iz, 1.);
#endif

#ifdef DEBUGIZIL
  gl_FragColor = vec4(Iz*Il, Iz*Il, Iz*Il, 1.);
#endif

#ifdef DEBUGIZINIL
  gl_FragColor = vec4(Iz*In*Il, Iz*In*Il, Iz*In*Il, 1.);
#endif

#ifdef DEBUGSHOWCOL
  gl_FragColor = texture2D(colorTex, gl_TexCoord[0].xy);
#endif

#ifdef DEBUGSHOWDEPTH
  gl_FragColor = vec4(texture2D(distanceTex, gl_TexCoord[0].xy).xxx, 1.);
#endif

#ifdef DEBUGSHOWGRAD
  gl_FragColor = vec4(texture2D(distanceTex, gl_TexCoord[0].xy).yyy, 1.);
#endif

}

