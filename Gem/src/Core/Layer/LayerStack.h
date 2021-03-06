#pragma once

#include "Layer.h"

namespace Gem
{

	class LayerStack
	{
		std::vector<Layer*> m_LayerVector;
		unsigned int m_LayerVectorIndex = 0;

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
