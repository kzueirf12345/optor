#include "optics/OpticObj.hpp"
#include "optics/Material.hpp"
#include <cassert>

optor::OpticObj::OpticObj()
    :   material_(),
        mustRemoved_(false)
{}

optor::OpticObj::OpticObj(const Material& material)
    :   material_(material),
        mustRemoved_(false)
{}

bool optor::OpticObj::GetMustRemoved() const {
    return mustRemoved_;
}
void optor::OpticObj::SetMustRemoved(bool mustRemoved) {
    mustRemoved_ = mustRemoved;
}

void optor::OpticObj::WriteSerialize(FILE* file, size_t baseTabCnt) const  {
    std::string baseIndent(baseTabCnt, ' ');
    std::string innerIndent(baseTabCnt + 4, ' ');
    
    fprintf(file, "%s\"material\": {\n", baseIndent.c_str());
    
    fprintf(file, "%s\"ambient\": [%g, %g, %g],\n", 
            innerIndent.c_str(), 
            material_.GetAmbientColor().x, 
            material_.GetAmbientColor().y, 
            material_.GetAmbientColor().z
    );
    
    fprintf(file, "%s\"diffuse\": [%g, %g, %g],\n", 
            innerIndent.c_str(), 
            material_.GetDiffuseColor().x, 
            material_.GetDiffuseColor().y, 
            material_.GetDiffuseColor().z
    );
    
    fprintf(file, "%s\"specular\": [%g, %g, %g],\n", 
            innerIndent.c_str(), 
            material_.GetSpecularColor().x, 
            material_.GetSpecularColor().y, 
            material_.GetSpecularColor().z
    );
    
    fprintf(file, "%s\"shininess\": %g,\n", innerIndent.c_str(), material_.GetShininess());
    fprintf(file, "%s\"reflectivity\": %g,\n", innerIndent.c_str(), material_.GetReflectivity());
    fprintf(file, "%s\"refractivity\": %g,\n", innerIndent.c_str(), material_.GetRefractivity());
    fprintf(file, "%s\"transparency\": %g\n", innerIndent.c_str(), material_.GetTransparency());

    fprintf(file, "%s},\n", baseIndent.c_str());
}