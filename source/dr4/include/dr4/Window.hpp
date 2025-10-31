#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_WINDOW_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_WINDOW_HPP

#include <memory>

#include "hui/Drawable.hpp"
#include "hui/Event.hpp"
#include "hui/Renderer.hpp"
#include "hui/Vector.hpp"

namespace hui 
{

class WindowImpl;

class Window : public hui::Renderer {
    public:
        Window(const hui::Vector2d& size, const std::string& title);

        Window           (const Window&) = delete;
        Window& operator=(const Window&) = delete;
        
        Window           (Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        ~Window();

        [[nodiscard]] virtual const void* GetImpl() const noexcept override final;
        [[nodiscard]] virtual       void* GetImpl()       noexcept override final;
        
        virtual       void Clear(const hui::Color& color) override;
        virtual       void Draw(const hui::Drawable& drawable) override;
        virtual       void Display() override;
        [[nodiscard]] bool isOpen() const;
                      void Close();
                      bool PoolEvent(hui::Event* event);
        void               SetFrameLimit(unsigned int limit);


        [[nodiscard]] hui::Vector2d GetSize() const;

    private:
        std::unique_ptr<WindowImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_WINDOW_HPP*/