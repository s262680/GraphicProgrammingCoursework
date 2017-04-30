#version 120

varying vec2 texCoord0;

uniform sampler2D diffuse;

const float offset = 1.5 / 300;  


void main()
{ 
   vec2 offsets[9] = vec2[](
	vec2(-offset, offset),  // top-left
	vec2(0.0f,    offset),  // top-center
	vec2(offset,  offset),  // top-right
	vec2(-offset, 0.0f),    // center-left
	vec2(0.0f,    0.0f),    // center-center
	vec2(offset,  0.0f),    // center-right
	vec2(-offset, -offset), // bottom-left
	vec2(0.0f,    -offset), // bottom-center
	vec2(offset,  -offset)  // bottom-right    
    );

    float kernel[9] = float[](
    1.0f/16, 2.0f/16, 1.0f/16,
    2.0f/16,  4.0f/16, 2.0f/16,
    1.0f/16, 2.0f/16, 1.0f/16
    );
    
    vec3 sampleTex[9];



    for(int i = 0; i < 9; i++)
    {
	sampleTex[i] = vec3(texture2D(diffuse, texCoord0.st + offsets[i]));
    }
	
	vec3 col=vec3(0.0);
	for(int i =0;i<9;i++)
	{
	col+=sampleTex[i]*kernel[i];
	}
	gl_FragColor=vec4(1.0,1.0,1.0,1.0) -vec4(col,1.0);
}