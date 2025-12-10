#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TEXT_BOX_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TEXT_BOX_HPP

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include <memory>

namespace optor 
{

class TextBox: public Widget, public Textable {
    public:

        TextBox(const dr4::Vec2f& size, optor::WidgetsState* state, const std::string& text);
        
        virtual bool OnMousePress(const dr4::Event &evt) override;
        virtual bool OnMouseRelease(const dr4::Event &evt) override;
        virtual bool OnMouseMove(const dr4::Event &evt) override;
        virtual bool OnKeyboardPress(const dr4::Event &evt) override;
        virtual bool OnTextInput(const dr4::Event &evt) override;

        virtual void Draw(dr4::Texture& srcTexture) override;

        virtual void SetPosition(const dr4::Vec2f& position) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "TextBox"; };
        
    protected:
        std::unique_ptr<dr4::Texture> texture_;

        std::string textStr_;

        bool keyHandled_;

        mutable std::unique_ptr<dr4::Text> tempText_;

        double prevClickTime_;
        double doubleClickDelay_;

        std::unique_ptr<dr4::Line> caret_;
        double caretBlinkPeriod_;
        mutable double caretPrevBlinkTime_;
        size_t caretPos_;
        bool caretIsHide_;

        bool inSelectMode_;
        size_t selectPos_;
        bool isSelectedSmth_;
        std::unique_ptr<dr4::Rectangle> selectedTextRect_;

    protected:

        size_t FindLetterPos(float mousePosX) const;

        bool HandleTextFinish(const dr4::Event::KeyEvent& evt);
        bool HandleBackspace(const dr4::Event::KeyEvent& evt);
        bool HandleDelete(const dr4::Event::KeyEvent& evt);
        bool HandleArrowLeft(const dr4::Event::KeyEvent& evt);
        bool HandleArrowRight(const dr4::Event::KeyEvent& evt);
        bool HandleA(const dr4::Event::KeyEvent& evt);
        bool HandleC(const dr4::Event::KeyEvent& evt);
        bool HandleV(const dr4::Event::KeyEvent& evt);
        bool HandleX(const dr4::Event::KeyEvent& evt);
        bool HandleHome(const dr4::Event::KeyEvent& evt);
        bool HandleEnd(const dr4::Event::KeyEvent& evt);

        void EraseLeftText();
        void EraseRightText();
        void EraseSelectedText();
        void InsertText(const std::string& addedText);

        void UpdateCaret();
        void UpdateSelectedTextRect();

        void SetSelectPos(size_t selectPos);
        void SetCaretPos(size_t pos);

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_TEXT_BOX_HPP*/