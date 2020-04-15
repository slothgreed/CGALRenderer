#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Renderer
{
class RenderData;
class DLL_EXPORT IMaterial
{
public:
	IMaterial();
	virtual ~IMaterial() {};

	virtual const MATERIAL_TYPE Type() const = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	virtual shared_ptr<IShader> CompileShader(IVertexBuffer* pVertexBuffer) = 0;
	virtual bool Compare(const IMaterial& material) = 0;
	void Draw(RenderData* pRenderData);

protected:
	shared_ptr<IShader> m_pShader;
	bool m_bReCompileShader;
};
}
}
#endif IMATERIAL_H
