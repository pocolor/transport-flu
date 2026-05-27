#include "tf/pch.hpp"

#include "LayerStack.hpp"

namespace tf {
    LayerStack::LayerStack() : m_layerInsert(m_layers.begin()) {
    }

    LayerStack::~LayerStack() {
        for (const Layer* layer : m_layers) {
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* layer) {
        m_layerInsert = m_layers.emplace(m_layerInsert, layer);
        layer->onAttach();
    }

    void LayerStack::popLayer(Layer *layer) {
        auto it = std::ranges::find(m_layers, layer);

        if (it != m_layers.end()) {
            m_layers.erase(it);
            layer->onDetach();
            --m_layerInsert;
        }
    }

    void LayerStack::pushOverlay(Layer *overlay) {
        m_layers.emplace_back(overlay);
        overlay->onAttach();
    }

    void LayerStack::popOverlay(Layer *overlay) {
        auto it = std::ranges::find(m_layers, overlay);

        if (it != m_layers.end()) {
            m_layers.erase(it);
            overlay->onDetach();
        }
    }
}
