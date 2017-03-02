##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=EscherEncryption
ConfigurationName      :=Release
WorkspacePath          := "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/EscherEncryption"
ProjectPath            := "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/EscherEncryption"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=d
Date                   :=11/25/14
CodeLitePath           :="/home/d/.codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="EscherEncryption.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall  -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Encryption_list.c$(ObjectSuffix) $(IntermediateDirectory)/Encryption_main.c$(ObjectSuffix) $(IntermediateDirectory)/Encryption_params.c$(ObjectSuffix) $(IntermediateDirectory)/Encryption_print_utils.c$(ObjectSuffix) $(IntermediateDirectory)/Encryption_reference.c$(ObjectSuffix) $(IntermediateDirectory)/Encryption_util.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Encryption_list.c$(ObjectSuffix): ../list.c $(IntermediateDirectory)/Encryption_list.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Encryption_list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Encryption_list.c$(DependSuffix): ../list.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Encryption_list.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Encryption_list.c$(DependSuffix) -MM "../list.c"

$(IntermediateDirectory)/Encryption_list.c$(PreprocessSuffix): ../list.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Encryption_list.c$(PreprocessSuffix) "../list.c"

$(IntermediateDirectory)/Encryption_main.c$(ObjectSuffix): ../main.c $(IntermediateDirectory)/Encryption_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Encryption_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Encryption_main.c$(DependSuffix): ../main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Encryption_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Encryption_main.c$(DependSuffix) -MM "../main.c"

$(IntermediateDirectory)/Encryption_main.c$(PreprocessSuffix): ../main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Encryption_main.c$(PreprocessSuffix) "../main.c"

$(IntermediateDirectory)/Encryption_params.c$(ObjectSuffix): ../params.c $(IntermediateDirectory)/Encryption_params.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/params.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Encryption_params.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Encryption_params.c$(DependSuffix): ../params.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Encryption_params.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Encryption_params.c$(DependSuffix) -MM "../params.c"

$(IntermediateDirectory)/Encryption_params.c$(PreprocessSuffix): ../params.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Encryption_params.c$(PreprocessSuffix) "../params.c"

$(IntermediateDirectory)/Encryption_print_utils.c$(ObjectSuffix): ../print_utils.c $(IntermediateDirectory)/Encryption_print_utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/print_utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Encryption_print_utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Encryption_print_utils.c$(DependSuffix): ../print_utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Encryption_print_utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Encryption_print_utils.c$(DependSuffix) -MM "../print_utils.c"

$(IntermediateDirectory)/Encryption_print_utils.c$(PreprocessSuffix): ../print_utils.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Encryption_print_utils.c$(PreprocessSuffix) "../print_utils.c"

$(IntermediateDirectory)/Encryption_reference.c$(ObjectSuffix): ../reference.c $(IntermediateDirectory)/Encryption_reference.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/reference.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Encryption_reference.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Encryption_reference.c$(DependSuffix): ../reference.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Encryption_reference.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Encryption_reference.c$(DependSuffix) -MM "../reference.c"

$(IntermediateDirectory)/Encryption_reference.c$(PreprocessSuffix): ../reference.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Encryption_reference.c$(PreprocessSuffix) "../reference.c"

$(IntermediateDirectory)/Encryption_util.c$(ObjectSuffix): ../util.c $(IntermediateDirectory)/Encryption_util.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/d/DANILO/Kriptografija/PublicQuasigroupCryptography/LinearQuasigroups/C/c_implementation/Encryption/util.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Encryption_util.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Encryption_util.c$(DependSuffix): ../util.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Encryption_util.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Encryption_util.c$(DependSuffix) -MM "../util.c"

$(IntermediateDirectory)/Encryption_util.c$(PreprocessSuffix): ../util.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Encryption_util.c$(PreprocessSuffix) "../util.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-release/EscherEncryption"


