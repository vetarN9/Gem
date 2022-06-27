#pragma once

#include "OrthographicCamera.h"

#include "Core/Timer/Timestep.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

namespace Gem
{

	class OrthographicCameraController
	{
		float m_AspectRatio;
		float m_Zoom = 1.0f;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraSpeed = 30.0f;
		float m_RotationSpeed = 1.0f;
		float m_CameraRotation = 0.0f;

		OrthographicCamera m_Camera;

		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);

	public:
		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	};

}