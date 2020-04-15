#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
namespace Renderer
{
class RenderData;
class DLL_EXPORT ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Axis(RenderData* pRenderData);
	static void RenderPlane(RenderData* pRenderData); // レンダリング用の平面
	static void CubeSpace(const BDB& size, RenderData* pRenderData);
	// sectorNum : 横の分割数
	// stackNum : 縦の分割数
	static void Sphere(float radius, int sectorNum, int stackNum, RenderData* pRenderData);
private:
};
}
}
#endif	