#ifndef SHADER_MANAGER_H

struct ShaderBuildInfo;
class IShader;
class ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager* Instance();
	std::shared_ptr<IShader> FindOrNew(const ShaderBuildInfo& buildInfo);
	void Dispose();
private:
	std::shared_ptr<IShader> Generate(const ShaderBuildInfo& buildInfo);
	std::vector<std::shared_ptr<IShader>> m_pShaderList;
	static ShaderManager* m_Instance;
};

#endif // !SHADER_MANAGER_H
