#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H
namespace KI
{
class MouseInput
{
public:
	MouseInput() { m_press = 0; m_wheel = 0; };
	~MouseInput() {};

	void SetPosition(float x, float y) { m_position.x = x; m_position.y = y; };
	void SetEvent(MOUSE_EVENT mouseEvent) { m_event = mouseEvent; };
	void SetWheel(int wheel) { m_wheel = wheel; };
	void SetPress(MOUSE_BUTTON value) { m_press |= value; }
	void SetRelease(MOUSE_BUTTON value) { m_press &= ~value; }

	const glm::vec2& Position() const { return m_position; };
	MOUSE_EVENT Event() const { return m_event; };
	int Wheel() const { return m_wheel; };
	bool Press(MOUSE_BUTTON value) const { return m_press & value; }
	MOUSE_BUTTON Press() const { return (MOUSE_BUTTON)m_press; }
private:
	glm::vec2 m_position;
	glm::vec2 m_delta;
	MOUSE_EVENT m_event;
	unsigned int m_press;	//�@MOUSE_BUTTON
	int m_wheel;
};
}

#endif MOUSE_INPUT_H
