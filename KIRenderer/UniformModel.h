#ifndef UNIFORM_MODEL_H
#define UNIFORM_MODEL_H

namespace KI
{
namespace Renderer
{
struct ModelData
{
	mat4 modelMatrix;
	mat3 normalMatrix;
	mat4 ambient;
	vec4 diffuse;
	vec4 specular;
};

class DLL_EXPORT UniformModel : public UniformBuffer
{
public:
	UniformModel();
	~UniformModel();
	void Set(const ModelData& data);
};
}
}


#endif UNIFORM_MODEL_H