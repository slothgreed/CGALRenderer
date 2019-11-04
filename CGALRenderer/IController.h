#ifndef ICONTROLLER_H
#define ICONTROLLER_H

enum CONTROLER_TYPE : unsigned int
{
	CAMERA_CONTROLER,
	CAMERA_CONTROLER_NUM
};

class IControllerArgs;
class Mouse;
class IController
{
public:
	IController() {};
	~IController() {};

	virtual void SetArgs(std::shared_ptr<IControllerArgs> value) { assert(0); }
	virtual bool Down(const Mouse&  mouse) { return false; };
	virtual bool Up(const Mouse&  mouse) { return false; };
	virtual bool Move(const Mouse&  mouse) { return false; };
	virtual bool Wheel(const Mouse&  mouse) { return false; }
private:

};


#endif ICONTROLLER_H