#ifndef UNIFORM_MODEL_H
#define UNIFORM_MODEL_H

namespace KI
{
namespace ShaderLib
{
struct ModelData
{
	mat4 modelViewMatrix;
	mat4 modelMatrix;
	mat4 normalMatrix;
	int objectId;
};

class DLL_EXPORT UniformModel : public UniformBuffer
{
public:
	UniformModel();
	~UniformModel();
	void SetViewMatrix(const mat4x4& viewMatrix);
	void SetModelMatrix(const mat4x4& viewMatrix);
	void SetObjectId(int id);
	virtual void Bind() override;
private:
	mat4x4 m_viewMatrix;
	ModelData m_ModelData;
};
}
}


#endif UNIFORM_MODEL_H