namespace KI
{

PickCommand::PickCommand(shared_ptr<ICommandArgs> args)
	: ICommand(args)
{

}

PickCommand::~PickCommand()
{

}

CommandResult PickCommand::CanExecute()
{
	if (m_pArgs->Type() != PICK_COMMAND)
	{
		return CommandResult::Failed;
	}

	return CommandResult::Success;
}

CommandResult PickCommand::Execute()
{
	auto args = static_pointer_cast<PickCommandArgs>(m_pArgs);

	vec3 near = glm::unProject(
		vec3(args->screenPosition.x, args->screenPosition.y, 0),
		args->m_pCamera->ViewMatrix(),
		args->m_pCamera->Projection(),
		args->m_pViewport->GetScreen()
		);

	vec3 far = glm::unProject(
		vec3(args->screenPosition.x, args->screenPosition.y, 0),
		args->m_pCamera->ViewMatrix(),
		args->m_pCamera->Projection(),
		args->m_pViewport->GetScreen()
	);

	assert(0);

	return CommandResult::Failed;
}

}