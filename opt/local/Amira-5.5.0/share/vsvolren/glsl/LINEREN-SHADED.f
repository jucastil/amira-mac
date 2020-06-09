uniform vec4 u0v_lightDir;
uniform vec4 u0v_ambient;
uniform vec4 u0v_diffuse;

varying vec3 tangent;
varying vec4 color;

void main()
{
    vec3 cf;
    vec3 t = normalize(tangent);

    float LdotT  = dot( u0v_lightDir.xyz, t );
    float LdotT2 = LdotT * LdotT;
    float LdotN  = sqrt( abs(1.0 - LdotT2) );
    float VdotR  = LdotN * sqrt( abs(1.0 - 2.0 * LdotT2) );

    cf  = u0v_ambient.rgb;
    cf += u0v_diffuse.rgb * LdotN;

    //cf += gl_LightSource[0].specular.rgb *
    //      gl_FrontMaterial.specular.rgb *
    //      pow(VdotR,gl_FrontMaterial.shininess);

    cf += vec3(1.0) * pow( VdotR, 25.0 );

    gl_FragColor = vec4( color.rgb * cf, color.a );
}
