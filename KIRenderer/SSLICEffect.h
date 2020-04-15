#ifndef SSLIC_EFFECT_H
#define SSLIC_EFFECT_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT SSLICEffect : public IPostEffect
{
public:
	SSLICEffect();
	~SSLICEffect();
	
	virtual PFX_TYPE Type() { return PFX_TYPE::PFX_TYPE_SSLIC; }
	virtual void Initialize(int width, int height) override;
	virtual void Draw() override;
	virtual void Resize(int width, int height) override;
	void SetRenderData(shared_ptr<RenderData> pRenderData);

	//virtual void ReadFromXML(const boost::property_tree::ptree& tree);
	//virtual void WriteToXML(const boost::property_tree::ptree& tree);

private:
	shared_ptr<Texture> m_pNoizeTexture;
	shared_ptr<Texture> m_pBlendTexture;
	shared_ptr<SSLICShader> m_pSSLICShader;
	shared_ptr<DefaultShader> m_pModelShader;
	shared_ptr<RenderData> m_pModelData;
	shared_ptr<RenderData> m_pPlaneData;
	shared_ptr<RenderTarget> m_pRenderTarget;

	shared_ptr<UniformSet> m_pModelUniform;
	shared_ptr<UniformSet> m_pSSLICUniform;
};
}
}
#endif SSLIC_EFFECT_H