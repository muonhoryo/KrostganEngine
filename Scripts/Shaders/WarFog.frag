
void main()
{
	float x = gl_PointCoord.x;
	float y = gl_PointCoord.y;

	gl_FragColor= vec4(0.1,0.1,0.1,0.5);
	//gl_FragColor = vec4(mod(x+y,5)/5, mod(x-y+5,5)/5, mod(y-x+5,5)/5, 1);
}