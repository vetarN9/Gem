#pragma once

#include "Core/Layer/Layer.h"

namespace Gem
{

	class GEM_API ImGuiLayer : public Layer
	{
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	};

}