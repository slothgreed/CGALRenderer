#ifndef DEFAULT_VERTEX_BUFFER_H
#define DEFAULT_VERTEX_BUFFER_H
namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultVertexBuffer : public IVertexBuffer
{
public:
	DefaultVertexBuffer();
	~DefaultVertexBuffer();
	virtual VERTEX_BUFFER_TYPE Type() { return VERTEX_BUFFER_TYPE::VERTEX_BUFFER_TYPE_DEFAULT; }
	virtual void BindAttribDivisor() override;
	virtual void UnBindAttribDivisor() override;

	void SetPosition(const vector<vec3>& position);
	void SetNormal(const vector<vec3>& normal);
	void SetColor(const vector<vec3>& color);
	void SetTexcoord(const vector<vec2>& texcoord);
	void SetInstanceMatrix(const vector<mat4>& matrix);
	VERTEX_LAYOUT Layout();
	bool HasAttribute(VERTEX_ATTRIB attribute);
private:
};
}
}
#endif VERTEX_BUFFER_H
