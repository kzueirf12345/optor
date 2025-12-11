#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_CHANGE_FIELD_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_CHANGE_FIELD_HPP

#include <functional>
#include <stdexcept>
#include "dr4/event.hpp"
#include "dr4/math/vec2.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Vector.hpp"
#include "widgets/TextBox.hpp"
#include "common/ErrorHandler.hpp"
#include "common/Utils.hpp"

namespace optor 
{

template<typename DataT>
class ChangeField: public TextBox {
    public:

        using SetT = std::function<void(OpticObj*, DataT)>;
        using GetT = std::function<DataT(OpticObj*)>;

    public:

        ChangeField(const dr4::Vec2f& size, optor::WidgetsState* state, const std::string& text, 
                    SetT setAction, GetT getAction, OpticObj* obj);

        virtual void OnIdle() override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "ChangeField"; };
        
    protected:

        virtual bool HandleTextFinish(const dr4::Event::KeyEvent& evt) override;
    
        SetT setAction_;
        GetT getAction_;
        DataT data_;
        OpticObj* obj_;

    private:
};

template<typename DataT>
optor::ChangeField<DataT>::ChangeField(const dr4::Vec2f& size, optor::WidgetsState* state, 
                                       const std::string& text, SetT setAction, GetT getAction, 
                                       OpticObj* obj)
    :   TextBox(size, state, text),
        setAction_(setAction),
        getAction_(getAction),
        obj_(obj),
        data_(getAction(obj))
{}

template<typename> struct is_vector3 : std::false_type {};
template<typename T> struct is_vector3<Vector3<T>> : std::true_type {};
template<typename T> inline constexpr bool is_vector3_v = is_vector3<T>::value;

template<typename DataT>
bool optor::ChangeField<DataT>::HandleTextFinish(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_ENTER) {
        try {
            if constexpr (std::is_same_v<DataT, double>) {
                data_ = std::stod(textStr_);
            } 
            else if constexpr (is_vector3_v<DataT>) {
                using ValueType = decltype(DataT::x);
                data_ = optor::Vector3Parse<ValueType>(textStr_);
            }
            else {
                throw std::invalid_argument("Unknown Type");
            }
        } 
        catch (...) {
            return false;
        }

        ERROR_HANDLE(setAction_, obj_, data_);
        state_->needUpdateScene = true;

        return true;
    }

    return false;
}

template <typename DataT>
void optor::ChangeField<DataT>::OnIdle() {
    if (isHide_) return;

    const DataT curData = getAction_(obj_);

    if (data_ != curData) {
        data_ = std::move(curData);

        if constexpr (std::is_same_v<DataT, double>) {
            textStr_ = common::to_string(data_);
        } 
        else if constexpr (std::is_same_v<DataT, optor::Vector3d>) {
            textStr_ = common::to_string(data_.x) + ", "
                     + common::to_string(data_.y) + ", "
                     + common::to_string(data_.z);
        }
        else {
            throw std::invalid_argument("Unknown Type");
        }

        text_->SetText(textStr_);
        caretPos_ = textStr_.size();

        isSelectedSmth_ = false;
        inSelectMode_ = false;

        UpdateCaret();
    }
}

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_CHANGE_FIELD_HPP*/