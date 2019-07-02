/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */

#ifndef cmBuildKitLinkLineComputer_h
#define cmBuildKitLinkLineComputer_h

#include "cmConfigure.h" // IWYU pragma: keep

#include <string>

#include "cmLinkLineComputer.h"

class cmGlobalBuildKitGenerator;
class cmOutputConverter;
class cmStateDirectory;

class cmBuildKitLinkLineComputer : public cmLinkLineComputer
{
public:
  cmBuildKitLinkLineComputer(cmOutputConverter* outputConverter,
                          cmStateDirectory const& stateDir,
                          cmGlobalBuildKitGenerator const* gg);

  cmBuildKitLinkLineComputer(cmBuildKitLinkLineComputer const&) = delete;
  cmBuildKitLinkLineComputer& operator=(cmBuildKitLinkLineComputer const&) = delete;

  std::string ConvertToLinkReference(std::string const& input) const override;

private:
  cmGlobalBuildKitGenerator const* GG;
};

#endif
