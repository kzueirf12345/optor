#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP

#include <memory>

#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "widgets/WidgetsState.hpp"

namespace optor {

class Widget;
class WidgetChildable;
    
class WidgetManager {
    public:
        WidgetManager(dr4::Window* window);

        WidgetManager           (const WidgetManager&) = delete;
        WidgetManager& operator=(const WidgetManager&) = delete;
        WidgetManager           (WidgetManager&&)      = delete;
        WidgetManager& operator=(WidgetManager&&)      = delete;

        void Draw();
        void HandleEvents();
        
        optor::WidgetChildable* SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop) ;

        [[nodiscard]] const optor::WidgetChildable* GetDesktop() const ;
        [[nodiscard]]       optor::WidgetChildable* GetDesktop()       ;
        [[nodiscard]] const optor::WidgetsState*    GetState()   const ;
        [[nodiscard]]       optor::WidgetsState*    GetState()         ;

    protected:

    private:
        dr4::Window* const window_;
        std::unique_ptr<dr4::Texture> texture_;
        std::unique_ptr<optor::WidgetChildable> desktop_;
        optor::WidgetsState state_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_MANAGER_HPP*/