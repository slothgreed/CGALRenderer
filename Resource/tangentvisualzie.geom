#include "common\common.h"
#include "common\struct.h"
layout(points) in;
layout(lines) out;

uniform float uLength;
in Data
{
	vec3 normal;
	vec3 tangent;
}InData[1];

void main()
{

	mat4 vp = scene.Projection * scene.ViewMatrix;

#ifdef VISIBLE_NORMAL
	gl_Position = vp * gl_in[0].gl_Position;
	EmitVertex();
	
	gl_Position = vp * vec4(gl_in[0].gl_Position.xyz + InData[0].normal*uLength,1.0);
	EmitVertex();
#endif
	
	gl_Position = vp * gl_in[0].gl_Position;
	EmitVertex();
	
	gl_Position = vp * vec4(gl_in[0].gl_Position.xyz + InData[0].tangent*uLength,1.0);
	EmitVertex();
	
	vec3 tangent2 = cross(InData[0].normal,InData[0].tangent);
	gl_Position = vp * gl_in[0].gl_Position;
	EmitVertex();
	
	gl_Position = vp * vec4(gl_in[0].gl_Position.xyz + InData[0].tangent2*uLength,1.0);
	EmitVertex();
	
	EndPrimitive();
}