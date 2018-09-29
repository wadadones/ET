mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

# Add o.file written in C
APPL_COBJS += \
	balancer.o \
	balancer_param.o \

# Add o.file written in C++
APPL_CXXOBJS += \
	BalancerCPP.o \
	Operator.o \
	EV3.o \
	Schedule.o \
	Phase.o \
	StartPhase.o \
	StraightPhase.o \
	CurvePhase.o \
	DetectGoal.o \
	DetectNansho.o \
	LookUpGateHandler.o \
	StairPhase.o \
	StairPhase2.o \
	StairPhase3.o \
	AfterGoal.o \
	GaragePhase.o \
	BeforeStair.o \
	ImmediatePhase.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

# Add directory has .c or .cpp files
APPL_DIR += \
	 $(mkfile_path)Balancer \
	 $(mkfile_path)Operator \
	 $(mkfile_path)EV3 \
	 $(mkfile_path)Schedule \
	 $(mkfile_path)Phase \
	 $(mkfile_path)Phase/StartPhase \
	 $(mkfile_path)Phase/StraightPhase \
	 $(mkfile_path)Phase/CurvePhase \
	 $(mkfile_path)Phase/DetectGoal \
	 $(mkfile_path)Phase/DetectNansho \
	 $(mkfile_path)Phase/LookUpGateHandler \
	 $(mkfile_path)Phase/StairPhase \
	 $(mkfile_path)Phase/StairPhase2 \
	 $(mkfile_path)Phase/StairPhase3 \
	 $(mkfile_path)Phase/AfterGoal \
	 $(mkfile_path)Phase/GaragePhase \
	 $(mkfile_path)Phase/BeforeStair \
	 $(mkfile_path)Phase/ImmediatePhase \

# Add directory has .h or .hpp files
INCLUDES += \
	-I$(mkfile_path)Balancer \
	-I$(mkfile_path)Operator \
	-I$(mkfile_path)EV3 \
	-I$(mkfile_path)Schedule \
	-I$(mkfile_path)Phase \
	-I$(mkfile_path)Phase/StartPhase \
	-I$(mkfile_path)Phase/StraightPhase \
	-I$(mkfile_path)Phase/CurvePhase \
	-I$(mkfile_path)Phase/DetectGoal \
	-I$(mkfile_path)Phase/DetectNansho \
	-I$(mkfile_path)Phase/LookUpGateHandler \
	-I$(mkfile_path)Phase/StairPhase \
	-I$(mkfile_path)Phase/StairPhase2 \
	-I$(mkfile_path)Phase/StairPhase3 \
	-I$(mkfile_path)Phase/AfterGoal \
	-I$(mkfile_path)Phase/GaragePhase \
	-I$(mkfile_path)Phase/BeforeStair \
	-I$(mkfile_path)Phase/ImmediatePhase \
