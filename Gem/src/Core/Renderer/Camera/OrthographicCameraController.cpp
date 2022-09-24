#include "gempch.h"

#include "Core/Renderer/Camera/OrthographicCameraController.h"

#include "Core/Input/Input.h"
#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseButtonCodes.h"

namespace Gem
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio* m_Zoom, -m_Zoom, m_Zoom)
	{
	}


	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		m_CameraSpeed = m_Zoom;

		if (Input::IsKeyPressed(GEM_KEY_A))
		{ 
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
		}

		if (Input::IsKeyPressed(GEM_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
		}

		if (Input::IsKeyPressed(GEM_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
		}

		if (Input::IsKeyPressed(GEM_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * timestep;
		}

		if (Input::IsKeyPressed(GEM_KEY_Q))
			m_CameraRotation -= m_RotationSpeed / 4;
		if (Input::IsKeyPressed(GEM_KEY_E))
			m_CameraRotation += m_RotationSpeed / 4;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(GEM_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(GEM_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Zoom -= event.GetOffsetY() * 0.25f;
		m_Zoom = std::clamp(m_Zoom, 0.25f, 7.5f);
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& event)
	{
		m_AspectRatio = ((float)event.GetWidth() / (float)event.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}

}