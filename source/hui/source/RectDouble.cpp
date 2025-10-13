#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "hui/RectDouble.hpp"
#include "common/ErrorHandler.hpp"

class hui::RectDoubleImpl: public sf::Rect<double> {
    public:
        RectDoubleImpl(const hui::Vector2d& size, const hui::Vector2d& position)
            :   sf::Rect<double>(
                    {size.x, size.y},
                    {position.x, position.y}
                )
        {}

    private:
};

hui::RectDouble::RectDouble(const hui::Vector2d& size)
    :   hui::RectDouble::RectDouble(size, {0, 0})
{}

hui::RectDouble::RectDouble(const hui::Vector2d& size, const hui::Vector2d& position)
    :   impl_{std::make_unique<hui::RectDoubleImpl>(size, position)}
{}

hui::RectDouble::~RectDouble() = default;

hui::RectDouble::RectDouble                (hui::RectDouble&& other) noexcept = default;
hui::RectDouble& hui::RectDouble::operator=(hui::RectDouble&& other) noexcept = default;

const void* hui::RectDouble::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::RectDouble::GetImpl() noexcept {
    return impl_.get();
}

hui::Vector2d hui::RectDouble::GetPosition() const noexcept {
    const auto* const impl = static_cast<const hui::RectDoubleImpl*>(GetImpl()); 
    return {impl->left, impl->top};
}

hui::Vector2d hui::RectDouble::GetSize() const noexcept {
    const auto* const impl = static_cast<const hui::RectDoubleImpl*>(GetImpl()); 
    return {impl->width, impl->height};
}

double hui::RectDouble::GetWidth() const noexcept {
    const auto* const impl = static_cast<const hui::RectDoubleImpl*>(GetImpl()); 
    return impl->width;
}

double hui::RectDouble::GetHeight() const noexcept {
    const auto* const impl = static_cast<const hui::RectDoubleImpl*>(GetImpl()); 
    return impl->height;
}

hui::Vector2d hui::RectDouble::GetRightCorner() const noexcept {
    const auto* const impl = static_cast<const hui::RectDoubleImpl*>(GetImpl()); 
    return {impl->left + impl->width, impl->top + impl->height};
}

void hui::RectDouble::SetPosition(const hui::Vector2d& position) noexcept {
    auto* const impl = static_cast<hui::RectDoubleImpl*>(GetImpl()); 
    impl->left = position.x;
    impl->top  = position.y;
}

void hui::RectDouble::SetSize    (const hui::Vector2d& size) noexcept {
    auto* const impl = static_cast<hui::RectDoubleImpl*>(GetImpl()); 
    impl->width  = size.x;
    impl->height = size.y;
}

bool hui::RectDouble::Contains(const hui::Vector2d& point) const {
    const auto* const impl = static_cast<const hui::RectDoubleImpl*>(GetImpl()); 
    return ERROR_HANDLE([impl, &point](){
        return impl->contains({point.x, point.y});
    });
}