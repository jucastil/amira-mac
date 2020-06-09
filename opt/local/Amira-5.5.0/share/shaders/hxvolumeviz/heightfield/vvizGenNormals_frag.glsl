uniform sampler2D heightTex;
uniform vec4 duDv;
uniform vec2 gridScale;

uniform float VVizHeightfieldScale;

vec3 computeGradient(vec2 tcoord)
{
  vec3 G = vec3(0, 0, 0);
  vec2 tmp = tcoord-duDv.xy-duDv.zw;

  //Scale to avoid precision error
  float scale = 1./VVizHeightfieldScale;

  float a00 = texture2D(heightTex,tmp).x;
  float a10 = texture2D(heightTex,tmp+duDv.xy).x;
  float a20 = texture2D(heightTex,tmp+2.*duDv.xy).x;

  tmp += duDv.zw;
  float a01 = texture2D(heightTex,tmp).x;
  float a11 = texture2D(heightTex,tmp+duDv.xy).x;
  float a21 = texture2D(heightTex,tmp+2.*duDv.xy).x;

  tmp += duDv.zw;
  float a02 = texture2D(heightTex,tmp).x;
  float a12 = texture2D(heightTex,tmp+duDv.xy).x;
  float a22 = texture2D(heightTex,tmp+2.*duDv.xy).x;

  float dx = -1./(gridScale.x*2.);
  float dy = -1./(gridScale.y*2.);

  vec3 e0 = vec3(0, dy, (a10-a11)*scale);
  vec3 e1 = vec3(dx, dy, (a20-a11)*scale);
  G += cross(e0, e1);

  e0 = e1;
  e1 = vec3(dx, 0, (a21-a11)*scale);
  G += cross(e0, e1);

  e0 = e1;
  e1 = vec3(dx, -dy, (a22-a11)*scale);
  G += cross(e0, e1);
  
  e0 = e1;
  e1 = vec3(0, -dy, (a12-a11)*scale);
  G += cross(e0, e1);

  e0 = e1;
  e1 = vec3(-dx, -dy, (a02-a11)*scale);
  G += cross(e0, e1);

  e0 = e1;
  e1 = vec3(-dx, 0, (a01-a11)*scale);
  G += cross(e0, e1);

  e0 = e1;
  e1 = vec3(-dx, dy, (a00-a11)*scale);
  G += cross(e0, e1);

  G.y = -G.y;

  return -normalize(G);
}

void main()
{
  vec3 n = computeGradient(gl_TexCoord[0].xy);

  //Stereographic projection
  n.x = n.x/(1.+n.z);
  n.y = n.y/(1.+n.z);
  n = (n+vec3(1.))*0.5;

  gl_FragColor =  vec4(n.xyz, 1.);
}
