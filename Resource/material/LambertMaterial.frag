#include "common\common.h"
#include "common\struct.h"
out vec4 outputColor;

#ifdef IN_TEXTURE
uniform sampler2D uTexture0;
in Data{
	in vec3 position;
	in vec3 normal;
	in vec2 texcoord;
}InData;
#endif

#ifdef IN_COLOR
in Data{
	in vec3 position;
	in vec3 normal;
	in vec4 color;
}InData;
#endif

#ifdef IN_FIXCOLOR
uniform vec4 uFixColor;
in Data{
	in vec3 position;
	in vec3 normal;
}InData;
#endif

vec4 GetColor()
{
#if defined(IN_TEXTURE)
	return texture2D(uTexture0,InData.texcoord);
#elif defined(IN_COLOR)
	return InData.color;
#elif defined(IN_FIXCOLOR)
	return uFixColor;
#endif
}

vec4 Lambert(vec4 surfaceColor)
{
	vec3 direction = normalize(light.Position.xyz);
	vec3 normal = normalize(InData.normal);
	float diffuse = clamp(dot(normal,direction),0.2,1.0);
	return diffuse * ((surfaceColor + light.Ambient) * light.Diffuse);
}

void main()
{
	outputColor = Lambert(GetColor());
}