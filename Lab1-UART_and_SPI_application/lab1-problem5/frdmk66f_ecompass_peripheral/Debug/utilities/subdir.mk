################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\utilities" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\drivers" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\accel" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\device" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\component\uart" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\component\lists" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\CMSIS" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\board" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\source" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\utilities" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\drivers" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\accel" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\device" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\component\uart" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\component\lists" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\CMSIS" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\board" -I"C:\Users\wuz147\Desktop\lab1-problem5\frdmk66f_ecompass_peripheral\frdmk66f\demo_apps\ecompass_peripheral" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

