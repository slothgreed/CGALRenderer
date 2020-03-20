#ifndef MANIPULATOR_NODE_H
#define MANIPULATOR_NODE_H

namespace KI
{
class ManipulatorNode : public IModelNode
{
public:
	ManipulatorNode();
	~ManipulatorNode();

	virtual void ShowProperty() override;
	virtual void Draw() override;
	virtual void Pick(const vec3& direction, PickResult& result) override;
private:
	void GenManipulatorHandleVBO(
		DefaultVertexBuffer* pFaceBuffer,
		IndexBuffer* pFaceIndexBuffer,
		DefaultVertexBuffer* pEdgeBuffer,
		IndexBuffer* pEdgeIndexBuffer, 
		MANIPULATOR_HANDLE handle);
	void SetRenderData();
	MoveManipulator manipulator;
	map<MANIPULATOR_HANDLE, DefaultVertexBuffer*> m_pFaceBuffers;
	map<MANIPULATOR_HANDLE, IndexBuffer*> m_pFaceIndexBuffers;
	map<MANIPULATOR_HANDLE, DefaultVertexBuffer*> m_pEdgeBuffers;
	map<MANIPULATOR_HANDLE, IndexBuffer*> m_pEdgeIndexBuffers;
	DefaultMaterial* m_pMaterial;
};
}


#endif MANIPULATOR_NODE_H