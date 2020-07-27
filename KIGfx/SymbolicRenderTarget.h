#ifndef SYMBOLIC_RENDERTARGET_H
#define	SYMBOLIC_RENDERTARGET_H

namespace KI
{
namespace Gfx
{
// GL_BACK, GL_FRONT �Ȃǂ�FBO���g��Ȃ��W���̃o�b�t�@�p
class DLL_EXPORT SymbolicRenderTarget : public IRenderTarget
{
public:
	SymbolicRenderTarget(GLenum drawBuffer);
	~SymbolicRenderTarget();

	virtual void Resize(int width, int height);
	virtual void Dispose();
	virtual int ColorTextureNum() override { return 1; };
	virtual bool GetPixels(ReadPixelArgs& args, RENDER_TEXTURE_TYPE type, int index = 0);

protected:
	virtual void Bind();
	virtual void UnBind();

private:
	GLenum m_drawBuffer;

};
}
}



#endif // !SYMBOLIC_RENDERTARGET_H
