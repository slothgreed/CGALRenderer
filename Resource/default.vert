
layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;

layout(location = 0) in vec3 position;
#ifdef USE_NORMAL
layout(location = 1) in vec3 normal;
#endif

#ifdef USE_COLOR
layout(location = 2) in vec3 color;
#endif

#ifdef USE_TEXCOORD
layout(location = 3) in vec2 texcoord;
out vec2 v_texcoord;
#else
out vec4 v_color;
#endif

#ifdef USE_GBUFFER
out vec4 v_position;
out vec4 v_normal;
#endif

#ifdef USE_INSTANCE
layout(location = 4) in vec4 instanceMatrix0;
layout(location = 5) in vec4 instanceMatrix1;
layout(location = 6) in vec4 instanceMatrix2;
layout(location = 7) in vec4 instanceMatrix3;
#endif

uniform vec4 uFixColor;

void main()
{
	mat4 vp = scene.Projection * scene.ViewMatrix;
#ifdef USE_INSTANCE
	mat4 instanceMatrix = mat4(instanceMatrix0,instanceMatrix1,instanceMatrix2,instanceMatrix3);
	gl_Position = vp * instanceMatrix * vec4(position,1.0);
#else
	gl_Position = vp * vec4(position,1.0);
#endif

#ifdef USE_COLOR
	v_color = vec4(color,1.0);
#elif defined(USE_NORMAL)
	v_color = vec4(normal,1.0);
#elif defined(USE_TEXCOORD)
	v_texcoord = texcoord;
#else 
	v_color = uFixColor;
#endif

#if defined(USE_GBUFFER) && defined(USE_NORMAL)
	v_position = gl_Position;
	v_normal = vec4(normal,1);
#elif defined(USE_GBUFFER)
	v_position = gl_Position;
	v_normal = vec4(1);
#endif

}