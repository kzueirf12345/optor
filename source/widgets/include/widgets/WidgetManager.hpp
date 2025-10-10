#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP

#include <memory>

#include "hui/Window.hpp"
#include "widgets/WidgetChildable.hpp"

namespace optor {
    
class WidgetManager {
    public:
        WidgetManager();

        WidgetManager           (const WidgetManager&) = delete;
        WidgetManager& operator=(const WidgetManager&) = delete;
        WidgetManager           (WidgetManager&&)      = delete;
        WidgetManager& operator=(WidgetManager&&)      = delete;

        void Draw(hui::Window* window);
        
        optor::WidgetChildable* SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop) noexcept;

        [[nodiscard]] const optor::WidgetChildable* GetDesktop() const noexcept;
        [[nodiscard]]       optor::WidgetChildable* GetDesktop()       noexcept;

    protected:

    private:
        std::unique_ptr<optor::WidgetChildable> desktop_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP*/