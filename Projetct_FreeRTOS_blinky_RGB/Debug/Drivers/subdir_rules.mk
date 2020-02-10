################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Drivers/%.obj: ../Drivers/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=1 --include_path="C:/Users/isaac/Documents/Workspace_v8/Projetct_FreeRTOS_blinky_RGB" --include_path="C:/ti/ccs831/ccsv8/tools/compiler/ti-cgt-arm_18.1.6.LTS/include" --include_path="C:/ti/FreeRTOSv10.2.1/FreeRTOS" --include_path="C:/ti/FreeRTOSv10.2.1/FreeRTOS/Source/include" --include_path="C:/ti/FreeRTOSv10.2.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/FreeRTOSv10.2.1/FreeRTOS/Source" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Drivers/$(basename $(<F)).d_raw" --obj_directory="Drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


