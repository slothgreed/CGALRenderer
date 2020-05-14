#ifndef VERTEX_MATERIAL_H
#define VERTEX_MATERIAL_H

namespace KI
{
namespace Asset
{
// no shading
class DLL_EXPORT VertexMaterial : public IMaterial
{
public:
	enum VERTEX_MATERIAL_TYPE
	{
		VERTEX_MATERIAL_POSITION,	// ���_�J���[
		VERTEX_MATERIAL_TEXCOORD,	// �e�N�X�`���F
		VERTEX_MATERIAL_NORMAL,		// �@���J���[
		VERTEX_MATERIAL_DEPTH,		// �f�v�X
	};

	VertexMaterial(VERTEX_MATERIAL_TYPE type);

	~VertexMaterial();


	VERTEX_MATERIAL_TYPE ColorType() { return m_Type; }
	virtual bool ShaderDefineComare(IMaterial* pMaterial) override;

private:
	VERTEX_MATERIAL_TYPE m_Type;

};

}
}

#endif BASIC_MATERIAL_H
