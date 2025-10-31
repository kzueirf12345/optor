#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_FONT_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_FONT_HPP

#include <memory>
#include <string>

namespace hui
{

class FontImpl;

class Font {
public:
    Font();
    explicit Font(const std::string& filename);

    Font           (const Font&) = delete;
    Font& operator=(const Font&) = delete;

    Font           (Font&& other) noexcept;
    Font& operator=(Font&& other) noexcept;

    virtual ~Font();

    [[nodiscard]] virtual const void* GetImpl() const noexcept;
    [[nodiscard]] virtual       void* GetImpl()       noexcept;

    void SetImpl(void* impl) noexcept;

    bool LoadFromFile(const std::string& filename);

private:
    std::unique_ptr<FontImpl> impl_;
};

}

#endif /* OPTOR_SOURCE_HUI_INCLUDE_HUI_FONT_HPP */
