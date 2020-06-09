#extension GL_EXT_geometry_shader4 : enable

varying in vec4 OivVertexLightSpace[];
varying out vec4 OivVertexLightSpaceGeom;
uniform float VVizUndefinedValue;

const float EPSILON = 0.0001;

void main()
{
  //check for undef value stored into texcoord z
  if ( abs(gl_TexCoordIn[0][0].z-VVizUndefinedValue) <= EPSILON ||
       abs(gl_TexCoordIn[1][0].z-VVizUndefinedValue) <= EPSILON ||
       abs(gl_TexCoordIn[2][0].z-VVizUndefinedValue) <= EPSILON )
     return;

  gl_Position = vec4(0.);
  gl_TexCoord[0] = vec4(0.);
  OivVertexLightSpaceGeom = vec4(0.);
  gl_FrontColor = vec4(0.);
  for(int i=0; i < 3; i++)
  {
    gl_Position = gl_PositionIn[i];
    gl_FrontColor = gl_FrontColorIn[i];
#ifndef OIV_USE_ATI
    gl_ClipVertex = gl_ClipVertexIn[i];
#endif
    gl_TexCoord[0] = gl_TexCoordIn[i][0];
    gl_TexCoord[1] = gl_TexCoordIn[i][1];
    gl_TexCoord[2] = gl_TexCoordIn[i][2];
    gl_TexCoord[3] = gl_TexCoordIn[i][3];
    gl_TexCoord[4] = gl_TexCoordIn[i][4];
    gl_TexCoord[5] = gl_TexCoordIn[i][5];
    gl_TexCoord[6] = gl_TexCoordIn[i][6];
    gl_TexCoord[7] = gl_TexCoordIn[i][7];
    OivVertexLightSpaceGeom = OivVertexLightSpace[i];

    EmitVertex();
  }
  EndPrimitive();
}

