#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXT_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXT_HPP

#include <memory>
#include <string>

#include "hui/Drawable.hpp"
#include "hui/Transformable.hpp"
#include "hui/Vector.hpp"
#include "hui/Color.hpp"

namespace hui
{

class TextImpl;
class Font;

class Text : public Drawable, public Transformable{
public:
    enum class Align {
        TopLeft,
        TopCenter,
        TopRight,
        CenterLeft,
        Center,
        CenterRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

    Text();
    explicit Text(const std::string& string);

    Text           (const Text&) = delete;
    Text& operator=(const Text&) = delete;

    Text           (Text&& other) noexcept;
    Text& operator=(Text&& other) noexcept;

    virtual ~Text();

    [[nodiscard]] virtual const void* GetImpl() const noexcept;
    [[nodiscard]] virtual       void* GetImpl()       noexcept;

    void SetImpl(void* impl) noexcept;

    void SetString(const std::string& string);
    void SetCharacterSize(unsigned int size);
    void SetFillColor(const hui::Color& color);
    void SetFont(const hui::Font& font);
    
    
    virtual void SetPosition(const hui::Vector2d& position);
    virtual hui::Vector2d GetPosition() const;
    
    [[nodiscard]] std::string     GetString()         const;
    [[nodiscard]] unsigned int    GetCharacterSize()  const;
    [[nodiscard]] uint32_t        GetFillColor()      const;
    [[nodiscard]] hui::Vector2d   GetSize() const;
    
private:
    std::unique_ptr<TextImpl> impl_;
};

}

#endif /* OPTOR_SOURCE_HUI_INCLUDE_HUI_TEXT_HPP */
