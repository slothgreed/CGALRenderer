namespace KI
{
namespace Renderer
{
PerspectiveCamera::PerspectiveCamera()
{
	m_theta = 0;
	m_phi = 0;
}
void PerspectiveCamera::Perspective(float fov, float aspect, float _near, float _far)
{
	SetProject(glm::perspective(fov, aspect, _near, _far));
	m_fov = fov;
	m_aspect = aspect;
	m_near = _near;
	m_far = _far;
}

void PerspectiveCamera::MoveWithSpherical(const vec2& move)
{
	SetTheta(move.x);
	SetPhi(move.y);

	vec3 sphericalPos;
	MathHelper::SphericalToCartesian(1.0f, glm::radians(Theta()), glm::radians(Phi()), sphericalPos);
	sphericalPos = glm::normalize(sphericalPos);
	sphericalPos *= LookAtDistance();
	sphericalPos += Center();
	LookAt(sphericalPos, Center(), Up());
}

void PerspectiveCamera::SetPhi(float value)
{
	if (m_phi + value >= 179.0f)
	{
		m_phi = 179.0f;
	}
	else if (m_phi + value <= 0.1f)
	{
		m_phi = 0.1f;
	}
	else
	{
		m_phi += value;
	}
}

void PerspectiveCamera::SetTheta(float value)
{
	if (m_theta + value >= 360.0f)
	{
		m_theta = 0.0f;
	}
	else if (m_theta + value <= -360.0f)
	{
		m_theta = 0.0f;
	}
	else
	{
		m_theta += value;
	}
}

void PerspectiveCamera::FitToBDB(const BDB& bdb)
{
	float lookAtDistance = glm::length(bdb.Max() - bdb.Center()) / (float)sin(m_fov / 2.0);
	lookAtDistance *= 1.2f / m_aspect;

	vec3 eyeDirection = glm::normalize(Eye() - Center());
	vec3 newPosition = bdb.Center() + eyeDirection * lookAtDistance;

	LookAt(newPosition, bdb.Center(), Up());
}

}
}