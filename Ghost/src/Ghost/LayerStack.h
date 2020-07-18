#pragma once

#include "Ghost/Core.h"
#include "Layer.h"

#include <vector>

namespace Ghost {
	class GHOST_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushLayerOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopLayerOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}