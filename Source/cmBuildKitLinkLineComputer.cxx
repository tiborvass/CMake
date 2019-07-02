/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */

#include "cmBuildKitLinkLineComputer.h"

#include "cmGlobalBuildKitGenerator.h"

class cmOutputConverter;

cmBuildKitLinkLineComputer::cmBuildKitLinkLineComputer(
  cmOutputConverter* outputConverter, cmStateDirectory const& stateDir,
  cmGlobalBuildKitGenerator const* gg)
  : cmLinkLineComputer(outputConverter, stateDir)
  , GG(gg)
{
}

std::string cmBuildKitLinkLineComputer::ConvertToLinkReference(
  std::string const& lib) const
{
  return GG->ConvertToBuildKitPath(lib);
}
