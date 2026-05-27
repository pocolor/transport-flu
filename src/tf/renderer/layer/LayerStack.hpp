#pragma once

#include "tf/core.hpp"

#include "Layer.hpp"

#include <vector>

namespace tf {
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void pushLayer(Layer *layer);
        void popLayer(Layer *layer);
        void pushOverlay(Layer *overlay);
        void popOverlay(Layer *overlay);

        auto begin() { return m_layers.begin(); }
        auto end() { return m_layers.end(); }

        auto begin() const { return m_layers.begin(); }
        auto end() const { return m_layers.end(); }

        auto rbegin() { return m_layers.rbegin(); }
        auto rend() { return m_layers.rend(); }

        auto rbegin() const { return m_layers.rbegin(); }
        auto rend() const { return m_layers.rend(); }

    private:
        std::vector<Layer*> m_layers;
        std::vector<Layer*>::iterator m_layerInsert;
    };
}
