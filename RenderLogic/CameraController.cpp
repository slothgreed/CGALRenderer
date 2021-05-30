namespace KI
{
namespace Logic
{
CameraController::CameraController(shared_ptr<CameraControllerArgs> pArgs)
{
	m_pArgs = static_pointer_cast<CameraControllerArgs>(pArgs);
	m_ZoomRatio = 0.1f;
}

CameraController::~CameraController()
{
}

void CameraController::SetArgs(shared_ptr<IControllerArgs> pArgs)
{
	m_pArgs = static_pointer_cast<CameraControllerArgs>(pArgs);
}
bool CameraController::Move(const Mouse& mouse)
{
	if (mouse.Press(KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT))
	{
		vec2 move = mouse.Delta();
		move.x *= 0.3f;
		move.y *= -0.3f;
		Rotate(move);
	}
	else if(mouse.Press(KI_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE))
	{
		vec2 move = mouse.Delta();
		move.x *= -0.3f;
		move.y *= 0.3f;
		Translate(move);
	}

	return true;
}

bool CameraController::Wheel(const Mouse&  mouse)
{
	if (mouse.Wheel() > 0)
	{
		Zoom(1 + m_ZoomRatio);
	}
	else
	{
		Zoom(1 - m_ZoomRatio);
	}

	return true;
}

void CameraController::Zoom(float ratio)
{
	if (m_pArgs->m_pCamera->Type() == CAMERA_TYPE::CAMERA_TYPE_PERSPECTIVE)
	{
		auto pCamera = m_pArgs->m_pCamera.get();
		vec3 eyeDirect = pCamera->Direction();
		float len = pCamera->LookAtDistance() * ratio;

		vec3 newEye = eyeDirect * len + pCamera->Center();

		pCamera->LookAt(newEye, pCamera->Center(), pCamera->Up());
	}
	else
	{
		OrthoCamera* pCamera = (OrthoCamera*)m_pArgs->m_pCamera.get();
		OrthoCamera::OrthoParameter param;
		pCamera->GetOrtho(&param);

		vec3 center = pCamera->GetCenter();

		param.m_left	= center.x + (param.m_left - center.x) * ratio;
		param.m_right	= center.x + (param.m_right - center.x) * ratio;
		param.m_bottom	= center.y + (param.m_bottom - center.y) * ratio;
		param.m_top		= center.y + (param.m_top - center.y) * ratio;

		pCamera->Ortho(param);
	}
}

void CameraController::Rotate(const vec2& move)
{
	if (m_pArgs->m_pCamera->Type() == CAMERA_TYPE::CAMERA_TYPE_PERSPECTIVE)
	{
		PerspectiveCamera* pCamera = (PerspectiveCamera*)m_pArgs->m_pCamera.get();
		pCamera->MoveWithSpherical(move);
	}
}

void CameraController::Translate(const vec2& move)
{
	if (m_pArgs->m_pCamera->Type() == CAMERA_TYPE::CAMERA_TYPE_PERSPECTIVE)
	{
		PerspectiveCamera* pCamera = (PerspectiveCamera*)m_pArgs->m_pCamera.get();
		vec3 xDir = pCamera->XDirection() * move.x;
		vec3 yDir = pCamera->YDirection() * move.y;
		vec3 eye = pCamera->Eye() + xDir + yDir;
		vec3 center = pCamera->Center() + xDir + yDir;
		pCamera->LookAt(eye, center, pCamera->Up());
	}
	else
	{
		OrthoCamera* pCamera = (OrthoCamera*)m_pArgs->m_pCamera.get();
		OrthoCamera::OrthoParameter orthoParam;
		pCamera->GetOrtho(&orthoParam);

		orthoParam.m_left += move.x;
		orthoParam.m_right += move.x;
		orthoParam.m_top += move.y;
		orthoParam.m_bottom += move.y;

		pCamera->Ortho(orthoParam);
	}
}
}
}