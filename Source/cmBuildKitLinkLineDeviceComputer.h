/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */

#ifndef cmBuildKitLinkLineDeviceComputer_h
#define cmBuildKitLinkLineDeviceComputer_h

#include "cmConfigure.h" // IWYU pragma: keep

#include <string>

#include "cmLinkLineDeviceComputer.h"

class cmGlobalBuildKitGenerator;
class cmOutputConverter;
class cmStateDirectory;

class cmBuildKitLinkLineDeviceComputer : public cmLinkLineDeviceComputer
{
public:
  cmBuildKitLinkLineDeviceComputer(cmOutputConverter* outputConverter,
                                cmStateDirectory const& stateDir,
                                cmGlobalBuildKitGenerator const* gg);

  cmBuildKitLinkLineDeviceComputer(cmBuildKitLinkLineDeviceComputer const&) = delete;
  cmBuildKitLinkLineDeviceComputer& operator=(
    cmBuildKitLinkLineDeviceComputer const&) = delete;

  std::string ConvertToLinkReference(std::string const& input) const override;

private:
  cmGlobalBuildKitGenerator const* GG;
};

#endif
