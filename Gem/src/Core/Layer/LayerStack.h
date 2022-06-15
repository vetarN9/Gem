#pragma once

#include "Core/Core.h"
#include "Layer.h"

namespace Gem
{

	class GEM_API LayerStack
	{
		std::vector<Layer*> m_LayerVector;
		std::vector<Layer*>::iterator m_LayerInsert;

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_LayerVector.begin(); }
		std::vector<Layer*>::iterator end() { return m_LayerVector.end(); }
	};

}
