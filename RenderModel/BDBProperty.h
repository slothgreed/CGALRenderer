#ifndef BDB_PROPERTY_H
#define BDB_PROEPRTY_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT BDBProperty : public IModelProperty
{
public:
	BDBProperty();
	~BDBProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_BDB; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void Update(IModelNode* pModel) override;
private:
	void GetBDBPosition(const BDB& bdb, vector<vec3>& position);
	void Build(IModelNode* pModel);
	shared_ptr<RenderData> m_pRenderData;
};
}
}

#endif // !BDB_PROPERTY_H
