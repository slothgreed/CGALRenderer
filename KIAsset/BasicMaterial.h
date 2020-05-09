#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

namespace KI
{
namespace Asset
{
// no shading
class DLL_EXPORT BasicMaterial : public IMaterial
{
public:
	enum BASIC_COLOR_TYPE
	{
		BASIC_COLOR_TYPE_FIX,		// �Œ�F
		BASIC_COLOR_TYPE_TEXTURE,	// �e�N�X�`���F
		BASIC_COLOR_TYPE_VERTEX,	// ���_�J���[
		BASIC_COLOR_TYPE_NORMAL,	// �@���J���[
		BASIC_COLOR_TYPE_DEPTH,		// �f�v�X
		BASIC_COLOR_TYPE_TEXCOORD,	// �e�N�X�`��
	};

	BasicMaterial(const vec4& color);
	BasicMaterial(shared_ptr<Texture> pTexture);
	BasicMaterial(BASIC_COLOR_TYPE type);

	~BasicMaterial();

	BASIC_COLOR_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);
private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	BASIC_COLOR_TYPE m_Type;

};

}
}

#endif BASIC_MATERIAL_H
