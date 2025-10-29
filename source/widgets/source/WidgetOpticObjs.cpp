#include <memory>

#include "common/ErrorHandler.hpp"
#include "widgets/WidgetOpticObjs.hpp"
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
                hui::Vector2d{size.x, 100}, 
                state, 
                obj->get()
            ));
        }));
        
        const size_t ind = obj - objs.begin();
        std::cerr << ind << "\n";

        child->SetPosition(hui::Vector2d{0, 100. * ind});
    }
}