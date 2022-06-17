#include "gempch.h"
#include "LayerStack.h"

#include <vector>

namespace Gem
{

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerVector)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerVector.emplace(m_LayerVector.begin() + m_LayerVectorIndex, layer);
		m_LayerVectorIndex++;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerVector.begin(), m_LayerVector.end(), layer);
		if (it != m_LayerVector.end()) 
		{
			m_LayerVector.erase(it);
			m_LayerVectorIndex--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerVector.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_LayerVector.begin(), m_LayerVector.end(), overlay);
		if (it != m_LayerVector.end()) 
		{
			m_LayerVector.erase(it);
		}
	}
}