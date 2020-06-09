// Bump-mapping
varying vec3 eNormal;       // Normal in eye space
varying vec3 viewDir;
varying vec3 lightDir;       // Vertex to light vector in eye space

void main()
{
  vec4 ePosition = gl_ModelViewMatrix * gl_Vertex;   // Position in eye space
  eNormal = normalize(gl_NormalMatrix * gl_Normal);      // Normal in eye space

  lightDir = gl_LightSource[0].position.xyz;
  lightDir = normalize(lightDir);

  viewDir = -ePosition.xyz;

  gl_TexCoord[0] = gl_MultiTexCoord0;

  gl_Position = ftransform();

  gl_FrontColor = gl_Color;
}
