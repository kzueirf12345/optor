#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURE_HPP

#include "hui/Vector.hpp"
#include <memory>

namespace hui 
{

class TextureImpl;

class Texture {
    public:
        Texture();
        Texture(const hui::Vector2d& size);

        Texture           (const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        
        Texture           (Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        virtual ~Texture();

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;

    private:
        std::unique_ptr<TextureImpl> impl_;
};

}



#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURE_HPP*/