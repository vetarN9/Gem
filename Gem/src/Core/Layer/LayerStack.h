#pragma once

#include "Core/Layer/Layer.h"

namespace Gem
{

	class LayerStack
	{
		std::vector<Layer*> m_LayerVector;
		unsigned int m_LayerVectorIndex = 0;

	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_LayerVector.begin(); }
		std::vector<Layer*>::iterator end() { return m_LayerVector.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_LayerVector.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_LayerVector.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_LayerVector.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_LayerVector.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_LayerVector.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_LayerVector.rend(); }
	};

}
