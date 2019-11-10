Camera::Camera()
{
	m_theta = 0;
	m_phi = 0;
}

Camera::~Camera()
{
}

void Camera::LookAt(const vec3& eye, const vec3& center, const vec3& up)
{
	m_View = glm::lookAt(eye, center, up);
	m_eye = eye;
	m_center = center;
	m_up = up;
	m_direction = glm::normalize(m_eye - m_center);
	m_distance = glm::length(m_eye - m_center);
}

void Camera::Perspective(float fov, float aspect, float _near, float _far)
{
	m_Project = glm::perspective(fov, aspect, _near, _far);
	m_fov = fov;
	m_aspect = aspect;
	m_near = _near;
	m_far = _far;
}

void Camera::MoveWithSpherical(const vec2& move)
{
	SetTheta(move.x);
	SetPhi(move.y);

	vec3 sphericalPos;
	MathHelper::SphericalToCartesian(glm::radians(Theta()), glm::radians(Phi()), sphericalPos);
	sphericalPos = glm::normalize(sphericalPos);
	sphericalPos *= LookAtDistance();
	sphericalPos += Center();
	LookAt(sphericalPos, Center(), Up());
}

void Camera::SetPhi(float value)
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

void Camera::SetTheta(float value)
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

void Camera::FitToBDB(const BDB& bdb)
{
	float lookAtDistance = glm::length(bdb.Max() - bdb.Center()) / sin(m_fov / 2.0);
	lookAtDistance *= 1.2 / m_aspect;

	vec3 eyeDirection = glm::normalize(m_eye - m_center);
	vec3 newPosition = bdb.Center() + eyeDirection * lookAtDistance;

	LookAt(newPosition, bdb.Center(), m_up);
}