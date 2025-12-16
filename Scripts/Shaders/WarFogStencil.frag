
uniform int count;
uniform float zoom;

layout(std430, binding = 0) buffer ObserversData
{
    vec4 observersInfo[];
};

void main()
{
    vec2 obsrPos;
    vec2 diff;
    float squareLen;
    float g=count;
    vec2 pixCoord=vec2
        (gl_FragCoord.x,
        gl_FragCoord.y);
        
    for(int offset=0; offset<count; offset++){

        obsrPos.x=observersInfo[offset].x;
        obsrPos.y=observersInfo[offset].y;
        diff.x=obsrPos.x-pixCoord.x;
        diff.y=obsrPos.y-pixCoord.y;   
        squareLen = diff.x * diff.x + diff.y * diff.y;
        if(squareLen <= (observersInfo[offset].z / zoom)){
            discard;
            return;
        }
    }
}