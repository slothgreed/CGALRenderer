#include "common\common.h"
#include "common\struct.txt"
#include "common\default.vbo"

out Data{

#ifdef OUT_NORMAL
out vec3 normal;
#endif

#ifdef OUT_COLOR
out vec4 color;
#endif
#ifdef OUT_TEXCOORD
out vec2 texcoord;
#endif
#ifdef OUT_INSTANCE
out vec4 instanceMatrix0;
out vec4 instanceMatrix1;
out vec4 instanceMatrix2;
out vec4 instanceMatrix3;
#endif

}OutData;

vec4 OutputColorExt()
{
#if defined(VIEW_POSITION)
	return vec4(a_position,1.0);
#elif defined(VIEW_COLOR)
	return vec4(a_color,1.0);
#elif defined(VIEW_NORMAL)
	return vec4(a_normal,1.0);
#elif defined(VIEW_TEXCOLOR)
	return vec4(a_texcoord.x,a_texcoord.y,0,1.0);
#elif defined(VIEW_DEPTH)
	return vec4(gl_Position.z,gl_Position.z,gl_Position.z,1.0);
#else
	return NotDefineColor();
#endif
}

void main()
{
	gl_Position = OutputPosition();

#if defined(OUT_NORMAL)
	OutData.normal = OutputNormal();
#endif

#if defined(OUT_COLOR)
	OutData.color = OutputColor();
#endif

#if defined(OUT_TEXCOORD)
	OutData.texcoord = OutputTexcoord();
#endif

#if defined(OUT_INSTANCE)
	OutData.instance0 = OutputInstance0();
	OutData.instance1 = OutputInstance1();
	OutData.instance2 = OutputInstance2();
	OutData.instance3 = OutputInstance3();
#endif
}