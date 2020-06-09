uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE rgba);

vec3 VVizComputeGradient(vec3 tcoord)
{
  vec3 G;
  vec3 tmp = tcoord-VVizDw-VVizDv-VVizDu;

  float a000 = VVizGetLuminance(VVizCombineData(tmp));
  float a100 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a200 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDw-VVizDu;
  float a010 = VVizGetLuminance(VVizCombineData(tmp));
  float a110 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a210 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDw-VVizDu+VVizDv;
  float a020 = VVizGetLuminance(VVizCombineData(tmp));
  float a120 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a220 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));


  tmp = tcoord-VVizDv-VVizDu;
  float a001 = VVizGetLuminance(VVizCombineData(tmp));
  float a101 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a201 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDu;
  float a011 = VVizGetLuminance(VVizCombineData(tmp));
  float a111 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a211 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDu+VVizDv;
  float a021 = VVizGetLuminance(VVizCombineData(tmp));
  float a121 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a221 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDv-VVizDu+VVizDw;
  float a002 = VVizGetLuminance(VVizCombineData(tmp));
  float a102 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a202 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDu+VVizDw;
  float a012 = VVizGetLuminance(VVizCombineData(tmp));
  float a112 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a212 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));

  tmp = tcoord-VVizDu+VVizDv+VVizDw;
  float a022 = VVizGetLuminance(VVizCombineData(tmp));
  float a122 = VVizGetLuminance(VVizCombineData(tmp+VVizDu));
  float a222 = VVizGetLuminance(VVizCombineData(tmp+2.*VVizDu));


  G.x = -a000 -3.*a001 -a002
        -3.*a010 -6.*a011 -3.*a012
        -a020-3.*a021-a022

        +a200 +3.*a201 +a202
        +3.*a210 +6.*a211 +3.*a212
        +a220 +3.*a221 +a222;

  G.y = -a000 - a100*3. - a200
        +a020 + a120*3. + a220

        -3.*a001 -6.*a101 -3.*a201
        +3.*a021 +6.*a121 +3.*a221

        -1.*a002 -3.*a102 -1.*a202
        +1.*a022 +3.*a122 +1.*a222;

  G.z = -a000 -3.*a010 -a020
        +a002 +3.*a012 +a022

        -3.*a100 -6.*a110 -3.*a210
        +3.*a102 +6.*a112 +3.*a212

        -a200 -3.*a210 -a220
        +a202 +3.*a212 +a222;

  G *= 1./(22.*sqrt(3.));
  return G;
}

vec3 VVizComputeGradient(sampler3D tex, vec3 tcoord)
{
  vec3 G;
  vec3 tmp = tcoord-VVizDw-VVizDv-VVizDu;

  float a000 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a100 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a200 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDw-VVizDu;
  float a010 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a110 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a210 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDw-VVizDu+VVizDv;
  float a020 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a120 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a220 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));


  tmp = tcoord-VVizDv-VVizDu;
  float a001 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a101 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a201 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDu;
  float a011 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a111 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a211 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDu+VVizDv;
  float a021 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a121 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a221 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDv-VVizDu+VVizDw;
  float a002 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a102 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a202 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDu+VVizDw;
  float a012 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a112 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a212 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));

  tmp = tcoord-VVizDu+VVizDv+VVizDw;
  float a022 = VVizGetLuminance(VVizGetData(tex, tmp));
  float a122 = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
  float a222 = VVizGetLuminance(VVizGetData(tex, tmp+2.*VVizDu));


  G.x = -a000 -3.*a001 -a002
        -3.*a010 -6.*a011 -3.*a012
        -a020-3.*a021-a022

        +a200 +3.*a201 +a202
        +3.*a210 +6.*a211 +3.*a212
        +a220 +3.*a221 +a222;

  G.y = -a000 - a100*3. - a200
        +a020 + a120*3. + a220

        -3.*a001 -6.*a101 -3.*a201
        +3.*a021 +6.*a121 +3.*a221

        -1.*a002 -3.*a102 -1.*a202
        +1.*a022 +3.*a122 +1.*a222;

  G.z = -a000 -3.*a010 -a020
        +a002 +3.*a012 +a022

        -3.*a100 -6.*a110 -3.*a210
        +3.*a102 +6.*a112 +3.*a212

        -a200 -3.*a210 -a220
        +a202 +3.*a212 +a222;

  G *= 1./(22.*sqrt(3.));
  return G;
}

