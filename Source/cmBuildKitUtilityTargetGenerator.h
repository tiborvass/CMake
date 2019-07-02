/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmBuildKitUtilityTargetGenerator_h
#define cmBuildKitUtilityTargetGenerator_h

#include "cmConfigure.h" // IWYU pragma: keep

#include "cmBuildKitTargetGenerator.h"

class cmGeneratorTarget;

class cmBuildKitUtilityTargetGenerator : public cmBuildKitTargetGenerator
{
public:
  cmBuildKitUtilityTargetGenerator(cmGeneratorTarget* target);
  ~cmBuildKitUtilityTargetGenerator() override;

  void Generate() override;
};

#endif // ! cmBuildKitUtilityTargetGenerator_h
