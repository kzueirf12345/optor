#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_BACKEND_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_BACKEND_HPP

#include "cum/ifc/pp.hpp"
#include <memory>

namespace optor 
{
namespace pp 
{

class PPToolPlugin final: public ::cum::PPToolPlugin {

public:

    virtual std::string_view GetIdentifier() const override;

    virtual std::string_view GetName() const override;

    virtual std::string_view GetDescription() const override;

    virtual std::vector<std::string_view> GetDependencies() const override;
    
    virtual std::vector<std::string_view> GetConflicts() const override;

    virtual void AfterLoad() override;

    virtual std::vector<std::unique_ptr<::pp::Tool>> CreateTools(::pp::Canvas *cvs) override;

private:

};

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_BACKEND_HPP*/