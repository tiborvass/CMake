/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmBuildKitTargetGenerator_h
#define cmBuildKitTargetGenerator_h

#include "cmConfigure.h" // IWYU pragma: keep

#include "cm_jsoncpp_value.h"

#include "cmCommonTargetGenerator.h"
#include "cmGlobalBuildKitGenerator.h"
#include "cmBuildKitTypes.h"
#include "cmOSXBundleGenerator.h"

#include <map>
#include <memory> // IWYU pragma: keep
#include <set>
#include <string>
#include <vector>

class cmCustomCommand;
class cmGeneratedFileStream;
class cmGeneratorTarget;
class cmLocalBuildKitGenerator;
class cmMakefile;
class cmSourceFile;

class cmBuildKitTargetGenerator : public cmCommonTargetGenerator
{
public:
  /// Create a cmBuildKitTargetGenerator according to the @a target's type.
  static std::unique_ptr<cmBuildKitTargetGenerator> New(
    cmGeneratorTarget* target);

  /// Build a BuildKitTargetGenerator.
  cmBuildKitTargetGenerator(cmGeneratorTarget* target);

  /// Destructor.
  ~cmBuildKitTargetGenerator() override;

  virtual void Generate() = 0;

  std::string GetTargetName() const;

  bool NeedDepTypeMSVC(const std::string& lang) const;

protected:
  bool SetMsvcTargetPdbVariable(cmBuildKitVars&) const;

  cmGeneratedFileStream& GetBuildFileStream() const;
  cmGeneratedFileStream& GetRulesFileStream() const;

  cmGeneratorTarget* GetGeneratorTarget() const
  {
    return this->GeneratorTarget;
  }

  cmLocalBuildKitGenerator* GetLocalGenerator() const
  {
    return this->LocalGenerator;
  }

  cmGlobalBuildKitGenerator* GetGlobalGenerator() const;

  cmMakefile* GetMakefile() const { return this->Makefile; }

  std::string LanguageCompilerRule(const std::string& lang) const;
  std::string LanguagePreprocessRule(std::string const& lang) const;
  bool NeedExplicitPreprocessing(std::string const& lang) const;
  std::string LanguageDyndepRule(std::string const& lang) const;
  bool NeedDyndep(std::string const& lang) const;
  bool UsePreprocessedSource(std::string const& lang) const;

  std::string BKOrderDependsTargetForTarget();

  std::string ComputeOrderDependsForTarget();

  /**
   * Compute the flags for compilation of object files for a given @a language.
   * @note Generally it is the value of the variable whose name is computed
   *       by LanguageFlagsVarName().
   */
  std::string ComputeFlagsForObject(cmSourceFile const* source,
                                    const std::string& language);

  void AddIncludeFlags(std::string& flags, std::string const& lang) override;

  std::string ComputeDefines(cmSourceFile const* source,
                             const std::string& language);

  std::string ComputeIncludes(cmSourceFile const* source,
                              const std::string& language);

  std::string ConvertToBuildKitPath(const std::string& path) const
  {
    return this->GetGlobalGenerator()->ConvertToBuildKitPath(path);
  }
  cmGlobalBuildKitGenerator::MapToBuildKitPathImpl MapToBuildKitPath() const
  {
    return this->GetGlobalGenerator()->MapToBuildKitPath();
  }

  /// @return the list of link dependency for the given target @a target.
  cmBuildKitDeps ComputeLinkDeps(const std::string& linkLanguage) const;

  /// @return the source file path for the given @a source.
  std::string GetSourceFilePath(cmSourceFile const* source) const;

  /// @return the object file path for the given @a source.
  std::string GetObjectFilePath(cmSourceFile const* source) const;

  /// @return the preprocessed source file path for the given @a source.
  std::string GetPreprocessedFilePath(cmSourceFile const* source) const;

  /// @return the dyndep file path for this target.
  std::string GetDyndepFilePath(std::string const& lang) const;

  /// @return the target dependency scanner info file path
  std::string GetTargetDependInfoPath(std::string const& lang) const;

  /// @return the file path where the target named @a name is generated.
  std::string GetTargetFilePath(const std::string& name) const;

  /// @return the output path for the target.
  virtual std::string GetTargetOutputDir() const;

  void WriteLanguageRules(const std::string& language);
  void WriteCompileRule(const std::string& language);
  void WriteObjectBuildStatements();
  void WriteObjectBuildStatement(cmSourceFile const* source);
  void WriteTargetDependInfo(std::string const& lang);

  void EmitSwiftDependencyInfo(cmSourceFile const* source);

  void ExportObjectCompileCommand(
    std::string const& language, std::string const& sourceFileName,
    std::string const& objectDir, std::string const& objectFileName,
    std::string const& objectFileDir, std::string const& flags,
    std::string const& defines, std::string const& includes);

  void AdditionalCleanFiles();

  cmBuildKitDeps GetObjects() const { return this->Objects; }

  void EnsureDirectoryExists(const std::string& dir) const;
  void EnsureParentDirectoryExists(const std::string& path) const;

  // write rules for macOS Application Bundle content.
  struct MacOSXContentGeneratorType
    : cmOSXBundleGenerator::MacOSXContentGeneratorType
  {
    MacOSXContentGeneratorType(cmBuildKitTargetGenerator* g)
      : Generator(g)
    {
    }

    void operator()(cmSourceFile const& source, const char* pkgloc) override;

  private:
    cmBuildKitTargetGenerator* Generator;
  };
  friend struct MacOSXContentGeneratorType;

  std::unique_ptr<MacOSXContentGeneratorType> MacOSXContentGenerator;
  // Properly initialized by sub-classes.
  std::unique_ptr<cmOSXBundleGenerator> OSXBundleGenerator;
  std::set<std::string> MacContentFolders;

  void addPoolBuildKitVariable(const std::string& pool_property,
                            cmGeneratorTarget* target, cmBuildKitVars& vars);

  bool ForceResponseFile();

private:
  cmLocalBuildKitGenerator* LocalGenerator;
  /// List of object files for this target.
  cmBuildKitDeps Objects;
  // Fortran Support
  std::map<std::string, cmBuildKitDeps> DDIFiles;
  // Swift Support
  Json::Value SwiftOutputMap;
  std::vector<cmCustomCommand const*> CustomCommands;
  cmBuildKitDeps ExtraFiles;
};

#endif // ! cmBuildKitTargetGenerator_h
