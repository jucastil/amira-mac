uniform sampler2D image;
uniform vec2 nextPos;

uniform vec2 texSize;
uniform vec2 invTexSize;

void main()
{
  vec2 tcoord = gl_TexCoord[0].xy;
  vec2 texUV = tcoord * texSize;
  vec2 texUVFrac = fract(texUV);
  vec2 texUVInt = floor(texUV)+0.5;
  tcoord = texUVInt*invTexSize;

  tcoord -= 3.*nextPos;
  vec4 p0 = texture2D(image, tcoord);
  tcoord += nextPos;
  vec4 p1 = texture2D(image, tcoord);
  tcoord += nextPos;
  vec4 p2 = texture2D(image, tcoord);
  tcoord += nextPos;
  vec4 p3 = texture2D(image, tcoord);
  tcoord += nextPos;
  vec4 p4 = texture2D(image, tcoord);
  tcoord += nextPos;
  vec4 p5 = texture2D(image, tcoord);
  tcoord += nextPos;
  vec4 p6 = texture2D(image, tcoord);

  vec4 res = 0.006*p0+0.061*p1+0.242*p2+0.383*p3+0.242*p4+0.061*p5+0.006*p6;
  res /= 0.006+0.061+0.242+0.383+0.242+0.061+0.006;

  gl_FragColor = res;
}
