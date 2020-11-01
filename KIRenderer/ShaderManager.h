#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager* Instance();
	static void Free();
	shared_ptr<IShader> FindOrNew(shared_ptr<IShaderBuildInfo> pBuildInfo);
	void Dispose();
private:
	shared_ptr<IShader> Generate(shared_ptr<IShaderBuildInfo> pBuildInfo);
	vector<shared_ptr<IShader>> m_pShaderList;
	static ShaderManager* m_Instance;
};

}
}
#endif // !SHADER_MANAGER_H
