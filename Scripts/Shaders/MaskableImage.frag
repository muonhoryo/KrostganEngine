
uniform sampler2D texture;
uniform sampler2D mask;
uniform float mask_threshold;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 maskPixel = texture2D(mask, gl_TexCoord[0].xy);

    if(maskPixel.r>mask_threshold){
        gl_FragColor = vec4(0,0,0,0);
    }
    else{
        gl_FragColor = gl_Color * pixel;
    }
}