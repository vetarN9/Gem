#include "gempch.h"
#include "Core/Layer/LayerStack.h"

namespace Gem
{

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerVector)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerVector.emplace(m_LayerVector.begin() + m_LayerVectorIndex, layer);
		m_LayerVectorIndex++;
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerVector.begin(), m_LayerVector.begin() + m_LayerVectorIndex, layer);
		if (it != m_LayerVector.begin() + m_LayerVectorIndex) 
		{
			layer->OnDetach();
			m_LayerVector.erase(it);
			m_LayerVectorIndex--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerVector.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_LayerVector.begin() + m_LayerVectorIndex, m_LayerVector.end(), overlay);
		if (it != m_LayerVector.end()) 
		{
			overlay->OnDetach();
			m_LayerVector.erase(it);
		}
	}
}