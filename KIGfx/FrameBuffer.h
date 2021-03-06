#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT FrameBuffer : public IGLObject
{
public:
	FrameBuffer();
	~FrameBuffer();

	virtual void Generate();
	virtual void Bind();
	virtual void UnBind();
	virtual void Dispose();
	bool Validate();
	void Clear();

private:
};
}
}
#endif // !FRAMEBUFFER_H
