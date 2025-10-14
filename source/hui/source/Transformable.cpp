#include "common/ErrorHandler.hpp"
#include "hui/Transformable.hpp"

#include <SFML/Graphics/Transformable.hpp>

class hui::TransformableImpl: public sf::Transformable {
    public:
    private:
};

hui::Transformable::Transformable(): impl_(std::make_unique<hui::TransformableImpl>()) {}

hui::Transformable::~Transformable() = default;

hui::Transformable::Transformable                (hui::Transformable&& other) noexcept = default;
hui::Transformable& hui::Transformable::operator=(hui::Transformable&& other) noexcept = default;

const void* hui::Transformable::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Transformable::GetImpl() noexcept {
    return impl_.get();
}

void hui::Transformable::SetPosition(const hui::Vector2d& position) { // FIXME
    ERROR_HANDLE([this, &position](){
        static_cast<hui::TransformableImpl*>(GetImpl())->setPosition(
            position.x, 
            position.y
        );}
    );
}

hui::Vector2d hui::Transformable::GetPosition() const { // FIXME
    const sf::Vector2f res = ERROR_HANDLE(
        &sf::Transformable::getPosition, 
        *static_cast<const hui::TransformableImpl*>(GetImpl())
    );
    return {res.x, res.y};
}
