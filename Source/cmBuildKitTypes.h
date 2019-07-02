/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmBuildKitTypes_h
#define cmBuildKitTypes_h

#include "cmConfigure.h" // IWYU pragma: keep

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

enum cmBuildKitTargetDepends
{
  BKDependOnTargetArtifact,
  BKDependOnTargetOrdering
};

typedef std::vector<std::string> cmBuildKitDeps;
typedef std::set<std::string> cmBuildKitOuts;
typedef std::map<std::string, std::string> cmBuildKitVars;

class cmBuildKitRule
{
public:
  cmBuildKitRule(std::string name)
    : Name(std::move(name))
  {
  }

  std::string Name;
  std::string Command;
  std::string Description;
  std::string Comment;
  std::string DepFile;
  std::string DepType;
  std::string RspFile;
  std::string RspContent;
  std::string Restat;
  bool Generator = false;
};

class cmBuildKitBuild
{
public:
  cmBuildKitBuild() = default;
  cmBuildKitBuild(std::string rule)
    : Rule(std::move(rule))
  {
  }

  std::string Comment;
  std::string Rule;
  cmBuildKitDeps Outputs;
  cmBuildKitDeps ImplicitOuts;
  cmBuildKitDeps ExplicitDeps;
  cmBuildKitDeps ImplicitDeps;
  cmBuildKitDeps OrderOnlyDeps;
  cmBuildKitVars Variables;
  std::string RspFile;
};

#endif // ! cmBuildKitTypes_h
