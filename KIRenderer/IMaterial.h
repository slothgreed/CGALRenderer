#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT IMaterial : public IShaderChunk
{
public:
	IMaterial() :m_bNeedRecompileShader(true) {};
	virtual ~IMaterial() {};

	void CompiledShader() { m_bNeedRecompileShader = false; }
	bool NeedReCompileShader() { return m_bNeedRecompileShader; };
private:
	bool m_bNeedRecompileShader;
};

}
}

#endif
