#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP

#include <optional>

#include "hui/Color.hpp"
#include "hui/Vector.hpp"

namespace optor 
{

class OpticObj {
    public:
        OpticObj();
        virtual ~OpticObj() = default;
        
        [[nodiscard]] virtual bool                      IsContainsDot(
                                                            const hui::Vector3d& dot
                                                        ) const noexcept = 0;
        [[nodiscard]] virtual std::optional<double>     IntersectRay(
                                                            const hui::Vector3d& rayBegin, 
                                                            const hui::Vector3d& rayDirection
                                                        ) const          = 0;

        [[nodiscard]] virtual hui::Vector3d GetNormal(const hui::Vector3d& dot) const = 0;

        [[nodiscard]] hui::Color GetAmbientColor() const noexcept;
        [[nodiscard]] hui::Color GetDiffColor()    const noexcept;
        [[nodiscard]] hui::Color GetSpecColor()    const noexcept;

        void SetAmbientColor(const hui::Color& color);
        void SetDiffColor   (const hui::Color& color);
        void SetSpecColor   (const hui::Color& color);

    protected:
        hui::Vector3d ambientColor_;
        hui::Vector3d diffColor_;
        hui::Vector3d specColor_;

    private:
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP*/