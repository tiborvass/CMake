/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmBuildKitNormalTargetGenerator_h
#define cmBuildKitNormalTargetGenerator_h

#include "cmConfigure.h" // IWYU pragma: keep

#include "cmGeneratorTarget.h"
#include "cmBuildKitTargetGenerator.h"

#include <string>
#include <vector>

class cmBuildKitNormalTargetGenerator : public cmBuildKitTargetGenerator
{
public:
  cmBuildKitNormalTargetGenerator(cmGeneratorTarget* target);
  ~cmBuildKitNormalTargetGenerator() override;

  void Generate() override;

private:
  std::string LanguageLinkerRule() const;
  std::string LanguageLinkerDeviceRule() const;

  const char* GetVisibleTypeName() const;
  void WriteLanguagesRules();

  void WriteLinkRule(bool useResponseFile);
  void WriteDeviceLinkRule(bool useResponseFile);

  void WriteLinkStatement();
  void WriteDeviceLinkStatement();

  void WriteObjectLibStatement();

  std::vector<std::string> ComputeLinkCmd();
  std::vector<std::string> ComputeDeviceLinkCmd();

private:
  // Target name info.
  cmGeneratorTarget::Names TargetNames;
  std::string TargetLinkLanguage;
  std::string DeviceLinkObject;
};

#endif // ! cmBuildKitNormalTargetGenerator_h
