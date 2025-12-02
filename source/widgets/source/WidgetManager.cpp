#include <memory>
#include <cassert>

#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "widgets/WidgetManager.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetPiska.hpp"

optor::WidgetManager::WidgetManager(dr4::Window* window, std::vector<cum::PPToolPlugin*> piskaPlugins)
    :   window_{window},
        texture_{window_->CreateTexture()},
        desktop_{},
        state_{}
{
    ERROR_HANDLE([this](){
        texture_->SetSize({optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT});
    });

    state_.window = window;

    desktop_ = ERROR_HANDLE([this, window](){
        return std::make_unique<optor::WidgetChildable>(
            dr4::Vec2f{optor::PROGRAM_WIDTH, optor::PROGRAM_HEIGHT},
            &state_
        );
    });
    ERROR_HANDLE(&optor::Widget::SetBackgroundColor, desktop_, optor::color::ProgramBackground);
    ERROR_HANDLE(&optor::Widget::SetIsDraggable, desktop_, false);

    state_.hoveredWidget = desktop_.get();
    state_.draggedWidget = nullptr;
    state_.selectedWidget = nullptr;
    state_.prevMouseCoord = {0, 0};
    state_.selectedObj = nullptr;
    state_.needUpdateScene = true;
    state_.piskaPlugins = std::move(piskaPlugins);
}

void optor::WidgetManager::Draw() {
    ERROR_HANDLE([this](){
        desktop_->Draw(*texture_);
    });

    for (auto& modalWidget : state_.modalWidgets) {
        ERROR_HANDLE([this, &modalWidget](){
            modalWidget->Draw(*texture_);
        });
    }

    auto* piska = dynamic_cast<optor::WidgetPiska*>(desktop_->GetChild(desktop_->GetChildrenCount() - 1));
    const bool piskaIsValid = piska && !piska->GetMustRemoved();

    if (piskaIsValid) {
        piska->Draw(*texture_);
    }

    ERROR_HANDLE([this](){
        window_->Draw(*texture_);
    });
}

void optor::WidgetManager::HandleEvents() {

    auto* piska = dynamic_cast<optor::WidgetPiska*>(desktop_->GetChild(desktop_->GetChildrenCount() - 1));
    const bool isSkip = piska && !piska->GetMustRemoved();
    
    std::optional<dr4::Event> event = {};

    while ((event = ERROR_HANDLE(&dr4::Window::PollEvent, window_))) {
        switch (event->type) {
            case dr4::Event::Type::QUIT:
                ERROR_HANDLE(&dr4::Window::Close, window_);
                return;

            case dr4::Event::Type::MOUSE_MOVE: {
                if (isSkip) {
                    ERROR_HANDLE(&optor::Widget::OnMouseMove, piska, event.value());
                    break;
                }
                bool childRes = false;
                for (auto& modalWidget : state_.modalWidgets) {
                    if (ERROR_HANDLE(&optor::Widget::OnMouseMove, modalWidget, event.value())) {
                        childRes = true;
                        state_.prevMouseCoord = event->mouseMove.pos;
                        break;
                    }
                }
                if (childRes) break;

                ERROR_HANDLE(&optor::WidgetChildable::OnMouseMove, desktop_, event.value());
                state_.prevMouseCoord = event->mouseMove.pos;
                break;
            }

            case dr4::Event::Type::MOUSE_DOWN: {
                if (isSkip) {
                    ERROR_HANDLE(&optor::Widget::OnMousePress, piska, event.value());
                    break;
                }
                bool childRes = false;
                for (auto& modalWidget : state_.modalWidgets) {
                    if (ERROR_HANDLE(&optor::Widget::OnMousePress, modalWidget, event.value())) {
                        childRes = true;
                        break;
                    }
                }
                if (childRes) break;

                ERROR_HANDLE(&optor::WidgetChildable::OnMousePress, desktop_, event.value());
                break;
            } 

            case dr4::Event::Type::MOUSE_UP: {
                if (isSkip) {
                    ERROR_HANDLE(&optor::Widget::OnMouseRelease, piska, event.value());
                    break;
                }
                bool childRes = false;
                for (auto& modalWidget : state_.modalWidgets) {
                    if (ERROR_HANDLE(&optor::Widget::OnMouseRelease, modalWidget, event.value())) {
                        childRes = true;
                        break;
                    }
                }
                if (childRes) break;

                ERROR_HANDLE(&optor::WidgetChildable::OnMouseRelease, desktop_, event.value());
                break;
            }

            case dr4::Event::Type::KEY_DOWN: {
                if (isSkip) {
                    ERROR_HANDLE(&optor::Widget::OnKeyboardPress, piska, event.value());
                    break;
                }
                if (event->key.sym == dr4::KEYCODE_TILDE) {
                    ERROR_HANDLE(
                        &optor::WidgetChildable::AddChild, 
                        desktop_, 
                        std::make_unique<optor::WidgetPiska>(&state_)
                    );
                }

                bool childRes = false;
                for (auto& modalWidget : state_.modalWidgets) {
                    if (ERROR_HANDLE(&optor::Widget::OnKeyboardPress, modalWidget, event.value())) {
                        childRes = true;
                        break;
                    }
                }
                if (childRes) break;

                ERROR_HANDLE(&optor::WidgetChildable::OnKeyboardPress, desktop_, event.value());
                break;
            }

            case dr4::Event::Type::KEY_UP: {
                if (isSkip) {
                    ERROR_HANDLE(&optor::Widget::OnKeyboardRelease, piska, event.value());
                    break;
                }
                bool childRes = false;
                for (auto& modalWidget : state_.modalWidgets) {
                    if (ERROR_HANDLE(&optor::Widget::OnKeyboardRelease, modalWidget, event.value())) {
                        childRes = true;
                        break;
                    }
                }
                if (childRes) break;

                ERROR_HANDLE(&optor::WidgetChildable::OnKeyboardRelease, desktop_, event.value());
                break;
            }

            case dr4::Event::Type::TEXT_EVENT: {
                if (isSkip) {
                    ERROR_HANDLE(&optor::Widget::OnTextInput, piska, event.value());
                    break;
                }
                bool childRes = false;
                for (auto& modalWidget : state_.modalWidgets) {
                    if (ERROR_HANDLE(&optor::Widget::OnTextInput, modalWidget, event.value())) {
                        childRes = true;
                        break;
                    }
                }
                if (childRes) break;

                ERROR_HANDLE(&optor::WidgetChildable::OnTextInput, desktop_, event.value());
                break;
            }

            default:
                break;
        }
    }

    if (!isSkip) {
        for (auto& modalWidget : state_.modalWidgets) {
            ERROR_HANDLE(&optor::Widget::OnIdle, modalWidget);
        }
    
        ERROR_HANDLE(&optor::WidgetChildable::OnIdle, desktop_);
    } else {
        ERROR_HANDLE(&optor::Widget::OnIdle, piska);
    }

}

optor::WidgetChildable* optor::WidgetManager::SetDesktop(std::unique_ptr<optor::WidgetChildable> desktop)  {
    desktop_ = std::move(desktop);
    state_.hoveredWidget = desktop_.get();
    return desktop_.get();
}
const optor::WidgetChildable* optor::WidgetManager::GetDesktop() const  {
    return desktop_.get();
}

optor::WidgetChildable* optor::WidgetManager::GetDesktop()  {
    return desktop_.get();
}

const optor::WidgetsState* optor::WidgetManager::GetState() const  {
    return &state_;
}

optor::WidgetsState* optor::WidgetManager::GetState()  {
    return &state_;
}
dr4::Window* optor::WidgetManager::GetWindow() {
    return window_;
}