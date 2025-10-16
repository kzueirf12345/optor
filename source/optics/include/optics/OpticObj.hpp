#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP

#include <optional>
#include <cstdint>

#include "hui/Vector.hpp"

namespace optor 
{

class OpticObj {
    public:
        virtual ~OpticObj() = default;
        
        [[nodiscard]] virtual bool                  IsContainsDot(
                                                        const hui::Vector3d& dot
                                                    ) const noexcept = 0;
        [[nodiscard]] virtual std::optional<double> IntersectRay(
                                                        const hui::Vector3d& rayBegin, 
                                                        const hui::Vector3d& rayDirection
                                                    ) const          = 0;
        [[nodiscard]] virtual uint32_t              TraceRay(
                                                        const hui::Vector3d& rayBegin, 
                                                        const hui::Vector3d& rayDirection
                                                    ) const          = 0;

    protected:
    private:
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP*/