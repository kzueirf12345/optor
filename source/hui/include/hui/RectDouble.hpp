#ifndef OPTOR_SOURCE_HUI_INCLUDE_HUI_RECT_HPP
#define OPTOR_SOURCE_HUI_INCLUDE_HUI_RECT_HPP

#include <memory>

#include "hui/Vector.hpp"

namespace hui 
{


class RectDoubleImpl;

class RectDouble {
    public:
        RectDouble(const hui::Vector2d& size, const hui::Vector2d& position = {});
        virtual ~RectDouble();

        RectDouble           (const RectDouble&) = delete;
        RectDouble& operator=(const RectDouble&) = delete;
        
        RectDouble           (RectDouble&& other) noexcept;
        RectDouble& operator=(RectDouble&& other) noexcept;

        [[nodiscard]] hui::Vector2d GetPosition()    const noexcept;
        [[nodiscard]] hui::Vector2d GetSize()        const noexcept;
        [[nodiscard]] double        GetWidth()       const noexcept;
        [[nodiscard]] double        GetHeigh()       const noexcept;
        [[nodiscard]] hui::Vector2d GetRightCorner() const noexcept;

        void SetPosition(const hui::Vector2d& position) noexcept;
        void SetSize    (const hui::Vector2d& size)     noexcept;

        [[nodiscard]] bool Contains(const hui::Vector2d& point) const;

        [[nodiscard]] virtual const void* GetImpl() const noexcept;
        [[nodiscard]] virtual       void* GetImpl()       noexcept;

    private:
        std::unique_ptr<hui::RectDoubleImpl> impl_;
};


}

#endif /*OPTOR_SOURCE_HUI_INCLUDE_HUI_RECT_HPP*/