#ifndef PICK_COMMAND_H
#define PICK_COMMAND_H

namespace KI
{

class PickCommandArgs : public ICommandArgs
{
	friend class PickCommand;

public:
	PickCommandArgs(
		shared_ptr<Viewport> viewport,
		shared_ptr<Camera> pCamera,
		vec2 position)
	{ 
		m_pViewport = viewport;
		m_pCamera = pCamera;
		screenPosition = position;
	};
	~PickCommandArgs() {};

	virtual COMMAND_ARGS_TYPE Type() { return SUBDIVISION_COMMAND_ARGS; }

private:
	shared_ptr<Viewport> m_pViewport;
	shared_ptr<Camera> m_pCamera;
	vec2 screenPosition;
};

class PickCommand : public ICommand
{

public :
	PickCommand(shared_ptr<ICommandArgs> args);
	~PickCommand();

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}

#endif // !PICK_COMMAND_H
