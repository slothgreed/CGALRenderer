namespace KI
{

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

CommandResult CommandManager::Execute(shared_ptr<ICommand> command)
{
	if (command->CanExecute() == CommandResult::Failed)
	{
		return CommandResult::Failed;
	}

	CommandResult result = command->Execute();
	if (result == CommandResult::Failed)
	{
		return CommandResult::Failed;
	}

	m_pCommandStack.push(command);

	return result;
}

CommandResult CommandManager::Undo()
{
	if (m_pCommandStack.size() == 0)
	{
		CommandResult::Failed;
	}

	auto command = m_pCommandStack.top();
	m_pCommandStack.pop(); // ���s������ȍ~Undo�ł��Ȃ��Ȃ�̂�h�����߂����Ŗ������폜

	CommandResult result = command->Undo();
	if (result == CommandResult::Failed)
	{
		assert(0);
		return CommandResult::Failed;
	}

	m_pUndoStack.push(command);

	return result;
}

CommandResult CommandManager::Redo()
{
	if (m_pUndoStack.size() == 0)
	{
		return CommandResult::Failed;
	}

	auto command = m_pUndoStack.top();
	CommandResult result = command->Execute();
	m_pUndoStack.pop(); // ���s������ȍ~Redo�ł��Ȃ��Ȃ�̂�h�����߂����Ŗ������폜

	if (result == CommandResult::Failed)
	{
		assert(0);
		return CommandResult::Failed;
	}

	return result;
}

int CommandManager::CommandNum()
{
	return m_pCommandStack.size();
}
}