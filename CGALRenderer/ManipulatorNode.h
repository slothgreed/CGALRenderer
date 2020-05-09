#ifndef MANIPULATOR_NODE_H
#define MANIPULATOR_NODE_H

namespace KI
{
class ManipulatorNode : public IModelNode
{
public:
	ManipulatorNode(MANIPULATOR_TYPE type);
	~ManipulatorNode();

	virtual void ShowProperty() override;
	virtual void Draw() override;
private:
	void GenManipulatorHandleVBO(
		RenderData* pFaceData,
		RenderData* pEdgeData,
		MANIPULATOR_HANDLE handle);
	void SetRenderData();
	map<MANIPULATOR_HANDLE, shared_ptr<RenderData>> m_pFaceDatas;
	map<MANIPULATOR_HANDLE, shared_ptr<RenderData>> m_pEdgeDatas;
	MANIPULATOR_TYPE m_ManipulatorType;
	shared_ptr<IManipulatorModel> m_pManipulator;
	shared_ptr<DefaultShaderPass> m_pShaderPass;
};
}


#endif MANIPULATOR_NODE_H