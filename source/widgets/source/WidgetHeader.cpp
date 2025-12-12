#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"

#include "widgets/WidgetHeader.hpp"
#include "dr4/mouse_buttons.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include <cstdlib>

optor::WidgetHeader::WidgetHeader(std::unique_ptr<optor::Widget> widget, 
                                  const std::string& title, CloseMode closeMode)
    :   Widget(
            widget->GetSize() 
                + dr4::Vec2f {
                    2 * (float)widget->GetOutlineThickness(), 
                    2 * (float)widget->GetOutlineThickness() + INIT_HEADER_HEIGHT
                }, 
            widget->GetState()
        ),
        optor::Textable(title, widget->GetState()->window),
        texture_{widget->GetState()->window->CreateTexture()},
        widget_{std::move(widget)},
        closeRect_(state_->window->CreateRectangle()),
        closeMode_(closeMode),
        closeText_(state_->window->CreateText())
{
    closeRect_->SetPos({
        rect_->GetSize().x - INIT_HEADER_HEIGHT - (float)widget_->GetOutlineThickness(), 
        (float)widget_->GetOutlineThickness()}
    );
    closeRect_->SetSize({INIT_HEADER_HEIGHT, INIT_HEADER_HEIGHT});
    closeRect_->SetFillColor(optor::color::ButtonReleased);
    closeRect_->SetBorderThickness(-2);
    closeRect_->SetBorderColor(optor::color::WindowBorder);

    closeText_->SetText("");
    closeText_->SetFont(optor::FONT);
    closeText_->SetColor(optor::color::TextPrimary);
    closeText_->SetFontSize(30);
    closeText_->SetPos(closeRect_->GetPos() + (closeRect_->GetSize() - closeText_->GetBounds()) / 2);//+ (closeRect_->GetSize() - closeText_->GetBounds()) / 2

    ERROR_HANDLE([this](){
        texture_->SetSize(rect_->GetSize());
    });

    SetDragButton(dr4::MouseButtonType::LEFT);
    SetPosition(widget_->GetPosition() + dr4::Vec2f{0, -INIT_HEADER_HEIGHT});
    SetParent(widget_->GetParent());
    SetBackgroundColor(optor::color::ButtonIdle);
    SetBorderColor(widget_->GetBorderColor());
    SetOutlineThickness(widget_->GetOutlineThickness());
    SetIsDraggable(widget_->GetIsDraggable());
    SetIsFreeDraggable(widget_->GetIsFreeDraggable());
    SetIsSelectable(widget_->GetIsSelectable());

    widget_->SetPosition({rect_->GetBorderThickness(), rect_->GetBorderThickness() + INIT_HEADER_HEIGHT});
    widget_->SetParent(this);
    // widget_->SetOutlineThickness(0);
    widget_->SetIsDraggable(false);
    widget_->SetIsFreeDraggable(false);

    ERROR_HANDLE([this](){
        const dr4::Vec2f localBounds = text_->GetBounds();
        const dr4::Vec2f size = rect_->GetSize();
        text_->SetPos(
            (size.x - localBounds.x - closeRect_->GetSize().x) / 2,
            (INIT_HEADER_HEIGHT - localBounds.y) / 2
        );
    });
}

void optor::WidgetHeader::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

void optor::WidgetHeader::Draw (dr4::Texture& srcTexture) 
{
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        widget_->Draw(*texture_);
    });

    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    ERROR_HANDLE([this](){
        texture_->Draw(*closeRect_);
    });

    ERROR_HANDLE([this](){
        texture_->Draw(*closeText_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

bool optor::WidgetHeader::OnMouseMove      (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    bool res = ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMouseMove(event);
    });

    if (ERROR_HANDLE([this, &event](){
            return widget_->OnMouseMove(event);
        })) 
    {
        return true;
    }

    return res;
}

bool optor::WidgetHeader::OnMousePress     (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
            return widget_->OnMousePress(event);
        })) 
    {
        return true;
    }

    if (dr4::Rect2f(AbsCoord() + closeRect_->GetPos(), closeRect_->GetSize()).Contains(event.mouseButton.pos)
     && event.mouseButton.button == dr4::MouseButtonType::LEFT
    ) {
        state_->hoveredWidget = parent_;
        if (closeMode_ == optor::WidgetHeader::CloseMode::HIDE) {
            isHide_ = true;
        } else {
            widget_.reset();
            mustRemoved_ = true;
        }
        return true;
    }

    dr4::Event newEvent(event);

    if (event.mouseButton.button == widget_->GetDragButton()) {
        newEvent.mouseButton.button = dragButton_;
    }

    return optor::Widget::OnMousePress(newEvent);
}

bool optor::WidgetHeader::OnMouseRelease   (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
            return widget_->OnMouseRelease(event);
        })) 
    {
        return true;
    }

    dr4::Event newEvent(event);

    if (event.mouseButton.button == widget_->GetDragButton()) {
        newEvent.mouseButton.button = dragButton_;
    }

    return optor::Widget::OnMouseRelease(newEvent);
}

bool optor::WidgetHeader::OnKeyboardPress  (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
            return widget_->OnKeyboardPress(event);
        })) 
    {
        return true;
    }

    return optor::Widget::OnKeyboardPress(event);
}

bool optor::WidgetHeader::OnKeyboardRelease(const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
            return widget_->OnKeyboardRelease(event);
        })) 
    {
        return true;
    }

    return optor::Widget::OnKeyboardRelease(event);
}

bool optor::WidgetHeader::OnTextInput(const dr4::Event& event) {
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
            return widget_->OnTextInput(event);
        })) 
    {
        return true;
    }

    return optor::Widget::OnTextInput(event);
}

void optor::WidgetHeader::OnIdle           () 
{
    if (isHide_) { return; }

    ERROR_HANDLE([this](){
        widget_->OnIdle();
    });
}

void optor::WidgetHeader::SetTitle(const std::string& title) {
    text_->SetText(title);
}
optor::Widget* optor::WidgetHeader::GetWidget() const {
    return widget_.get();
}