#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP

#include <memory>

#include "hui/Vector.hpp"
#include "hui/Window.hpp"

namespace optor {

class Widget;
class WidgetChildable;

struct WidgetsState {
    const optor::Widget* hoveredWidget;
    const optor::Widget* draggedWidget;
    hui::Vector2d        prevMouseCoord;
};
    
class WidgetManager {
    public:
        WidgetManager();

        WidgetManager           (const WidgetManager&) = delete;
        WidgetManager& operator=(const WidgetManager&) = delete;
        WidgetManager           (WidgetManager&&)      = delete;
        WidgetManager& operator=(WidgetManager&&)      = delete;

        void Draw(hui::Window* window);
        void HandleEvents(hui::Window* window);
        
        optor::WidgetChildable* SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop) noexcept;

        [[nodiscard]] const optor::WidgetChildable* GetDesktop() const noexcept;
        [[nodiscard]]       optor::WidgetChildable* GetDesktop()       noexcept;
        [[nodiscard]] const optor::WidgetsState*    GetState()   const noexcept;
        [[nodiscard]]       optor::WidgetsState*    GetState()         noexcept;

    protected:

    private:
        std::unique_ptr<optor::WidgetChildable> desktop_;
        optor::WidgetsState state_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP*/