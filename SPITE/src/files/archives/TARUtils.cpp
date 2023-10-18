#include "harmful/spite/files/archives/TARUtils.hpp"
#include "harmful/spite/third_party/microtar.h"

using namespace Spite ;

TARData TARUtils::Load(const std::string& path) {
    TARData tarData ;
    mtar_t tar ;
    tarData.initialize(tar, path, "r") ;
    tarData.read(tar) ;
    tarData.finalize(tar) ;
    return tarData ;
}

void TARUtils::Save(
    TARData& tarData,
    const std::string& path
) {
    mtar_t tar ;
    tarData.initialize(tar, path, "w") ;
    tarData.beforeWrite(tar) ;
    tarData.write(tar) ;
    tarData.finalize(tar) ;
}
