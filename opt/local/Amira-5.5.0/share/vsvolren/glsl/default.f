void main()
{
    gl_FragColor  = vec4( 1.0, 0.0, 1.0, 1.0 );

    int zeile  = int(gl_FragCoord.x) / 8;
    int spalte = int(gl_FragCoord.y) / 8;

    

    gl_FragColor *= vec4( (zeile+spalte) - ((zeile+spalte)/2)*2 );
}