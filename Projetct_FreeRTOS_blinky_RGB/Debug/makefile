################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./Drivers/buttons.obj" \
"./Drivers/rgb.obj" \
"./FreeRTOS/list.obj" \
"./FreeRTOS/queue.obj" \
"./FreeRTOS/tasks.obj" \
"./Portable/heap_2.obj" \
"./Portable/port.obj" \
"./Portable/portasm.obj" \
"./Utils/uartstdio.obj" \
"./Utils/ustdlib.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Drivers/subdir_vars.mk
-include FreeRTOS/subdir_vars.mk
-include Portable/subdir_vars.mk
-include Utils/subdir_vars.mk
-include subdir_rules.mk
-include Drivers/subdir_rules.mk
-include FreeRTOS/subdir_rules.mk
-include Portable/subdir_rules.mk
-include Utils/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Projetct_FreeRTOS_blinky_RGB.out \

EXE_OUTPUTS__QUOTED += \
"Projetct_FreeRTOS_blinky_RGB.out" \

BIN_OUTPUTS += \
Projetct_FreeRTOS_blinky_RGB.hex \

BIN_OUTPUTS__QUOTED += \
"Projetct_FreeRTOS_blinky_RGB.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Projetct_FreeRTOS_blinky_RGB.out"

# Tool invocations
Projetct_FreeRTOS_blinky_RGB.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=1 --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Projetct_FreeRTOS_blinky_RGB.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS/lib" -i"C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Projetct_FreeRTOS_blinky_RGB_linkInfo.xml" --rom_model -o "Projetct_FreeRTOS_blinky_RGB.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Projetct_FreeRTOS_blinky_RGB.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS/bin/armhex"  -o "Projetct_FreeRTOS_blinky_RGB.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "Drivers\buttons.obj" "Drivers\rgb.obj" "FreeRTOS\list.obj" "FreeRTOS\queue.obj" "FreeRTOS\tasks.obj" "Portable\heap_2.obj" "Portable\port.obj" "Portable\portasm.obj" "Utils\uartstdio.obj" "Utils\ustdlib.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "Drivers\buttons.d" "Drivers\rgb.d" "FreeRTOS\list.d" "FreeRTOS\queue.d" "FreeRTOS\tasks.d" "Portable\heap_2.d" "Portable\port.d" "Utils\uartstdio.d" "Utils\ustdlib.d" 
	-$(RM) "Portable\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

