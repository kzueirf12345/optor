#include "widgets/ColorRect.hpp"
#include "optics/Vector.hpp"
#include "widgets/Widget.hpp"

optor::ColorRect::ColorRect(const dr4::Vec2f& size, optor::WidgetsState* state, GetT getAction, 
                            OpticObj* obj)
    :   optor::Widget(size, state),
        getAction_(getAction),
        obj_(obj)
{}

void optor::ColorRect::OnIdle() {
    if (isHide_) return;

    const Vector3d curColor = getAction_(obj_);

    if (color_ != curColor) {
        color_ = std::move(curColor);

        rect_->SetFillColor({
            static_cast<uint8_t>(color_.x * 255), 
            static_cast<uint8_t>(color_.y * 255), 
            static_cast<uint8_t>(color_.z * 255), 
            255
        });
    }
}