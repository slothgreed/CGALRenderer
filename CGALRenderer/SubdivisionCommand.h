#ifndef SUBDIVISION_COMMAND_H
#define SUBDIVISION_COMMAND_H

class SubdivisionCommandArgs : public ICommandArgs
{
	friend class SubdivisionCommand;

public:
	SubdivisionCommandArgs(shared_ptr<IModel> model) { m_pModel = model; };
	~SubdivisionCommandArgs() {};

	virtual COMMAND_ARGS_TYPE Type() { return SUBDIVISION_COMMAND_ARGS; }

private:
	shared_ptr<IModel> m_pModel;
};


class SubdivisionCommand : public ICommand
{
public:
	SubdivisionCommand(shared_ptr<ICommandArgs> args);
	~SubdivisionCommand();

	virtual COMMAND_TYPE Type() { return SUBDIVISION_COMMAND; }
private:

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};



#endif // !SUBDIVISION_COMMAND_H

