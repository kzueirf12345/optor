#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_COLOR_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_COLOR_HPP

#include <memory>

namespace hui 
{

class ColorImpl;

class Color {
    public:
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
        ~Color();

        Color           (const Color&) = delete;
        Color& operator=(const Color&) = delete;
        
        Color           (Color&& other) noexcept;
        Color& operator=(Color&& other) noexcept;

        [[nodiscard]] uint8_t  GetRed()   const noexcept;
        [[nodiscard]] uint8_t  GetGreen() const noexcept;
        [[nodiscard]] uint8_t  GetBlue()  const noexcept;
        [[nodiscard]] uint8_t  GetAlpha() const noexcept;
        [[nodiscard]] uint32_t GetInt()   const noexcept;

        void SetRed     (uint8_t  red)    noexcept;
        void SetGreen   (uint8_t  green)  noexcept;
        void SetBlue    (uint8_t  blue)   noexcept;
        void SetAlpha   (uint8_t  alpha)  noexcept;
        void SetInt     (uint32_t color)  noexcept;

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;
        
    private:
        std::unique_ptr<hui::ColorImpl> impl_;
};

}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_COLOR_HPP*/