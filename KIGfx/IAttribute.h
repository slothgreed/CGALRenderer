#ifndef IATTRONITE_H
#define IATTRONITE_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IAttribute
{
public:
	IAttribute() {};
	~IAttribute() {};

	virtual SHADER_TYPE Type() = 0;
private:

};
}
}

#endif ISHADER_H