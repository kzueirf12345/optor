#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_WINDOW_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_WINDOW_HPP

#include <memory>

#include "hui/Drawable.hpp"
#include "hui/Event.hpp"
#include "hui/Vector.hpp"

namespace hui 
{

class WindowImpl;

class Window {
    public:
        Window(double width, double height, const std::string& title);

        Window           (const Window&) = delete;
        Window& operator=(const Window&) = delete;
        
        Window           (Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        ~Window();
        
                      void Clear();
                      void Draw(const hui::Drawable& drawable);
                      void Display();
        [[nodiscard]] bool isOpen() const;
                      void Close();
                      bool PoolEvent(hui::Event* event);

        [[nodiscard]] hui::Vector2d GetSize() const;

    private:
        std::unique_ptr<WindowImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_WINDOW_HPP*/