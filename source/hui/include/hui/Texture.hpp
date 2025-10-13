#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURE_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURE_HPP

#include <memory>
#include <vector>

#include "hui/Vector.hpp"
#include "hui/Color.hpp"

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

        void Update(const std::vector<uint32_t>& pixels);

    private:
        std::unique_ptr<TextureImpl> impl_;
};

}



#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXTURE_HPP*/