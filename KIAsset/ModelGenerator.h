#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Plane(RenderData* pRenderData, VERTEX_LAYOUT layout); // レンダリング用の平面
private:
};
}
}
#endif	