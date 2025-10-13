#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_RENDERER_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_RENDERER_HPP

#include <memory>

#include "hui/Color.hpp"
#include "hui/Vector.hpp"
#include "hui/Drawable.hpp"

namespace hui 
{

class RendererImpl;

class Renderer {
    public:
        Renderer(const hui::Vector2d& size);
        virtual ~Renderer();

        Renderer           (const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        
        Renderer           (Renderer&& other) noexcept;
        Renderer& operator=(Renderer&& other) noexcept;

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;

        virtual void Clear(const hui::Color& color = hui::Color(0, 0, 0));
        virtual void Draw(const hui::Drawable& drawable);
        virtual void Display();

        [[nodiscard]] hui::Vector2d GetSize() const;

    private:
        std::unique_ptr<RendererImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_RENDERER_HPP*/