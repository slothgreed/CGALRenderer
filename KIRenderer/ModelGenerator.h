#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
namespace Renderer
{
class DefaultVertexBuffer;
class DLL_EXPORT ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Axis(DefaultVertexBuffer* vertexBuffer);
	static void RenderPlane(DefaultVertexBuffer* vertexBuffer); // �����_�����O�p�̕���
	static void CubeSpace(const BDB& size, DefaultVertexBuffer* pVertexBuffer);
private:
};
}
}
#endif	