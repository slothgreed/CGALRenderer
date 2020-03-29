#ifndef ISHADER_CODE_H
#define ISHADER_CODE_H

namespace KI
{
namespace Gfx
{

class DLL_EXPORT IShaderCode
{
public:
	IShaderCode(const string& filePath) { m_filePath = filePath; };
	virtual ~IShaderCode() {};
	virtual void GetDefineCode(string& code) {};
	virtual SHADER_TYPE Type() = 0;
	virtual bool Compare(IShaderCode* pShaderCode) { return true; }
	void Load(string& code);

private:

	string m_filePath;
	string m_code;
};

}
}

#endif ISHADER_CODE_H