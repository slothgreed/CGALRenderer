#ifndef IPFX_EFFECT_H
#define IPFX_EFFECT_H

enum PFX_TYPE
{
	PFX_TYPE_GRAYSCALE,
	PFX_TYPE_SSLIC,
};
class IPostEffect
{
public:
	IPostEffect() : m_apply(true) {};
	~IPostEffect() {};

	virtual PFX_TYPE Type() = 0;
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Resize(int width, int height) = 0;
	void SetApply(bool value) { m_apply = value; }
	bool Apply() { return m_apply; }
private:
	bool m_apply;

};
#endif IPFX_EFFECT_H