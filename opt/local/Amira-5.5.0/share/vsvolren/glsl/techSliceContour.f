uniform sampler2D   u0s_Label;
uniform sampler1D   u0s_LookupLabel;
uniform vec4        u0v_ContourThickness;


// Routine to compute the material calssification for a pixel 
// with respect to the data at the current position and the 
// data samples left, right, above and below

float material( float data,   // the sample from the current raster position
                float left,   // the sample from the left neighboring pixel
                float right,  // the sample from the right neighboring pixel
                float down,   // the sample from the lower neighboring pixel
                float up      // the sample from the upper neighboring pixel
                )
{
    float eps = 0.5;

    // Left border and lower border
    bool entering = abs(left - data) > eps || abs(down - data) > eps;

    // Right border and upper border
    bool leaving = abs(right - data) > eps || abs(up - data) > eps;

    return (entering || leaving) ? data : -1.0;
}


void main()
{
    vec4 outColor = vec4(0.0);

#ifndef USE_ARB

    // Note that this function are currently not supported by the ARB profiles
    vec4 dx = dFdx(gl_TexCoord[0]);
    vec4 dy = dFdy(gl_TexCoord[0]);

    vec2 center   = gl_TexCoord[0].xy;
    vec2 left     = gl_TexCoord[0].xy - dx.xy;
    vec2 right    = gl_TexCoord[0].xy + dx.xy;
    vec2 down     = gl_TexCoord[0].xy - dy.xy;
    vec2 up       = gl_TexCoord[0].xy + dy.xy;

#else

    vec2 center   = gl_TexCoord[0].xy;
    vec2 left     = gl_TexCoord[0].xy - u0v_ContourThickness.xy;
    vec2 right    = gl_TexCoord[0].xy + u0v_ContourThickness.xy;
    vec2 down     = gl_TexCoord[0].xy - u0v_ContourThickness.zw;
    vec2 up       = gl_TexCoord[0].xy + u0v_ContourThickness.zw;

#endif

    float data; 
    vec4  neighbors;
    data        = texture2D( u0s_Label, center ).x;
    neighbors.x = texture2D( u0s_Label, left ).x;
    neighbors.y = texture2D( u0s_Label, right ).x;
    neighbors.z = texture2D( u0s_Label, down ).x;
    neighbors.w = texture2D( u0s_Label, up ).x;

    data *= 255.0;
    neighbors *= 255.0;

    // Voxels with the most significant label bit set will just be
    // considered selected voxels, they will be rendered according
    // to the seven remaining bits.
    vec4 offset = vec4(128.0);
    data -= (data > 127.5) ? offset.x : 0.0;
    neighbors -= vec4(greaterThan(neighbors,vec4(127.5))) * offset;

    float matVal = material(data, neighbors.x, neighbors.y, neighbors.z, neighbors.w);

    gl_FragColor = matVal < 0.0 ? 
                      outColor : 
                      texture1D( u0s_LookupLabel, (matVal + 0.5) / 255.0);
}
