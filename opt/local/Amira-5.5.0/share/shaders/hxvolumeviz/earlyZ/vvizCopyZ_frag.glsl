uniform sampler2D depthTex;
uniform vec3 texSizeInv;
uniform vec2 viewportSizeInv;

void main()
{
  vec2 tcoord = gl_FragCoord.xy*viewportSizeInv;

  if ( texSizeInv.xy != viewportSizeInv )
  {
	vec2 row0;
	row0.x = texture2D(depthTex, tcoord.xy).x;
	row0.y = texture2D(depthTex, tcoord.xy+texSizeInv.xz).x;

	vec2 row1;
	row1.x = texture2D(depthTex, tcoord.xy+texSizeInv.zy).x;
	row1.y = texture2D(depthTex, tcoord.xy+texSizeInv.xy).x;

	row0 = min(row0, row1);
	gl_FragDepth = min(row0.x, row0.y);
  }
  else
    gl_FragDepth = texture2D(depthTex, tcoord.xy).x;
}
