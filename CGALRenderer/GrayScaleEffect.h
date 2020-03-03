#ifndef GRAY_SCALE_EFFECT_H
#define GRAY_SCALE_EFFECT_H

namespace KI
{

class GrayScaleEffect : public IPostEffect
{
public:
	GrayScaleEffect();
	~GrayScaleEffect();

	virtual PFX_TYPE Type() { return PFX_TYPE::PFX_TYPE_GRAYSCALE; }
	virtual void Initialize() override;
	virtual void Draw() override;
	void Resize(int width, int height) override;

	void SetTexture(shared_ptr<Texture> texture);
	//virtual void ReadFromXML(const boost::property_tree::ptree& tree);
	//virtual void WriteToXML(const boost::property_tree::ptree& tree);

private:
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<Texture> m_pTexture;
	shared_ptr<DefaultVertexBuffer> m_pPlane;
	shared_ptr<GrayScaleShader> m_pGrayScaleShader;
	shared_ptr<GrayScaleUniform> m_pGrayUniform;
};
}


#endif GRAY_SCALE_EFFECT_H