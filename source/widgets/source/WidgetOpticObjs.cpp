#include <memory>

#include "common/ErrorHandler.hpp"
#include "widgets/WidgetOpticObjs.hpp"
#include "global/Global.hpp"
#include "hui/Vector.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetOpticObj.hpp"

optor::WidgetOpticObjs::WidgetOpticObjs(const hui::Vector2d& size, optor::WidgetsState* state, 
                                        const optor::Scene& scene)
    :   optor::WidgetChildable(size, state)
{
    const auto& objs = scene.GetObjs();
    for (auto obj = objs.begin(); obj != objs.end(); ++obj) {
        auto* child = dynamic_cast<optor::WidgetOpticObj*>(ERROR_HANDLE([&](){
            return this->AddChild(std::make_unique<optor::WidgetOpticObj>(
                hui::Vector2d{size.x, optor::STRING_BLOCK_HEIGHT}, 
                state, 
                obj->get()
            ));
        }));
        
        const size_t ind = obj - objs.begin();

        child->SetPosition(hui::Vector2d{0, optor::STRING_BLOCK_HEIGHT * ind});
    }
}

void optor::WidgetOpticObjs::Scroll(double percentage) {
    const double maxSize = children_.size() * optor::STRING_BLOCK_HEIGHT;
    const double diffSize = texture_.GetSize().y - maxSize;
    const double baseOffset = diffSize * percentage;

    for (size_t ind = 0; ind < children_.size(); ++ind) {
        auto* child = children_[ind].get();
        child->SetPosition(hui::Vector2d{0, baseOffset + optor::STRING_BLOCK_HEIGHT * ind});
    }
}