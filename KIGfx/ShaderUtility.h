#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT ShaderUtility
{
public:
	ShaderUtility();
	~ShaderUtility();
	
	static GLuint Compile(const string& code, GLuint shaderType);
	static GLuint Link(GLuint vertexId, GLuint tcsId, GLuint tesId, GLuint geomId, GLuint fragId);
	
	static void Load(string filePath, string& shaderCode);

	// �g�ݍ��ݎ��ʕ����񂪂���ꍇ�A���̈ʒu�ɕ������g�ݍ��ށA�Ȃ��ꍇ�g�ݍ��ݎ��ʕ�������폜����B
	// [in, out]	: code;
	// embeddedCode : �g�ݍ��ޕ�����
	// embeddedIdentifier : �g�ݍ��ވʒu�̕�����
	static void EmbeddedCode(string& code, const string& embeddedCode, const string& embeddedIdentifier);

private:
	// �V�F�[�_�R�[�h��W�J����.
	static void ExpandShaderCode(const string& filePath, string& shaderCode);

	static string m_shaderDirectory;

};
}
}

#endif SHADER_UTILITY_H
