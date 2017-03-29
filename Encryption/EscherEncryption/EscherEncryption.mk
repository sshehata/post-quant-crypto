##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=EscherEncryption
ConfigurationName      :=Debug
WorkspacePath          :=/home/sshehata/Projects/CodeLite
ProjectPath            :=/home/sshehata/Projects/post-quant-crypto/Encryption/EscherEncryption
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=03/10/17
CodeLitePath           :=/home/sshehata/.codelite
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
Preprocessors          :=
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
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall  -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_list.c$(ObjectSuffix) $(IntermediateDirectory)/up_main.c$(ObjectSuffix) $(IntermediateDirectory)/up_params.c$(ObjectSuffix) $(IntermediateDirectory)/up_print_utils.c$(ObjectSuffix) $(IntermediateDirectory)/up_reference.c$(ObjectSuffix) $(IntermediateDirectory)/up_util.c$(ObjectSuffix) $(IntermediateDirectory)/up_reference_s.c$(ObjectSuffix) $(IntermediateDirectory)/up_test.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_list.c$(ObjectSuffix): ../list.c $(IntermediateDirectory)/up_list.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_list.c$(DependSuffix): ../list.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_list.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_list.c$(DependSuffix) -MM ../list.c

$(IntermediateDirectory)/up_list.c$(PreprocessSuffix): ../list.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_list.c$(PreprocessSuffix) ../list.c

$(IntermediateDirectory)/up_main.c$(ObjectSuffix): ../main.c $(IntermediateDirectory)/up_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_main.c$(DependSuffix): ../main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_main.c$(DependSuffix) -MM ../main.c

$(IntermediateDirectory)/up_main.c$(PreprocessSuffix): ../main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_main.c$(PreprocessSuffix) ../main.c

$(IntermediateDirectory)/up_params.c$(ObjectSuffix): ../params.c $(IntermediateDirectory)/up_params.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/params.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_params.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_params.c$(DependSuffix): ../params.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_params.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_params.c$(DependSuffix) -MM ../params.c

$(IntermediateDirectory)/up_params.c$(PreprocessSuffix): ../params.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_params.c$(PreprocessSuffix) ../params.c

$(IntermediateDirectory)/up_print_utils.c$(ObjectSuffix): ../print_utils.c $(IntermediateDirectory)/up_print_utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/print_utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_print_utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_print_utils.c$(DependSuffix): ../print_utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_print_utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_print_utils.c$(DependSuffix) -MM ../print_utils.c

$(IntermediateDirectory)/up_print_utils.c$(PreprocessSuffix): ../print_utils.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_print_utils.c$(PreprocessSuffix) ../print_utils.c

$(IntermediateDirectory)/up_reference.c$(ObjectSuffix): ../reference.c $(IntermediateDirectory)/up_reference.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/reference.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_reference.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_reference.c$(DependSuffix): ../reference.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_reference.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_reference.c$(DependSuffix) -MM ../reference.c

$(IntermediateDirectory)/up_reference.c$(PreprocessSuffix): ../reference.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_reference.c$(PreprocessSuffix) ../reference.c

$(IntermediateDirectory)/up_util.c$(ObjectSuffix): ../util.c $(IntermediateDirectory)/up_util.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/util.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_util.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_util.c$(DependSuffix): ../util.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_util.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_util.c$(DependSuffix) -MM ../util.c

$(IntermediateDirectory)/up_util.c$(PreprocessSuffix): ../util.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_util.c$(PreprocessSuffix) ../util.c

$(IntermediateDirectory)/up_reference_s.c$(ObjectSuffix): ../reference_s.c $(IntermediateDirectory)/up_reference_s.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/reference_s.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_reference_s.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_reference_s.c$(DependSuffix): ../reference_s.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_reference_s.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_reference_s.c$(DependSuffix) -MM ../reference_s.c

$(IntermediateDirectory)/up_reference_s.c$(PreprocessSuffix): ../reference_s.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_reference_s.c$(PreprocessSuffix) ../reference_s.c

$(IntermediateDirectory)/up_test.c$(ObjectSuffix): ../test.c $(IntermediateDirectory)/up_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sshehata/Projects/post-quant-crypto/Encryption/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_test.c$(DependSuffix): ../test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_test.c$(DependSuffix) -MM ../test.c

$(IntermediateDirectory)/up_test.c$(PreprocessSuffix): ../test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_test.c$(PreprocessSuffix) ../test.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


