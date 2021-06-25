#pragma once

#include "Yama/Core/Common.h"
#include <vector>

namespace Yama
{
    class Layer;

    class YAMA_API LayerStack
    {
        using LayerIt = std::vector<Layer*>::iterator;
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        inline LayerIt begin() { return m_Layers.begin(); }
        inline LayerIt end() { return m_Layers.end(); }

    private:
        std::vector<Layer*> m_Layers;
        LayerIt m_LayerInsert;
    };
}