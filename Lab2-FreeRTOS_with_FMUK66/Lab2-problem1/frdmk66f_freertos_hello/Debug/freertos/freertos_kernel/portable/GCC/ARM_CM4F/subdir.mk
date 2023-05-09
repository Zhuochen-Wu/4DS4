################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.c 

C_DEPS += \
./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.d 

OBJS += \
./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/portable/GCC/ARM_CM4F/%.o: ../freertos/freertos_kernel/portable/GCC/ARM_CM4F/%.c freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\source" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\drivers" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\device" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\utilities" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\component\uart" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\component\serial_manager" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\component\lists" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\CMSIS" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\freertos\freertos_kernel\include" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\wuz147\Desktop\Lab2-problem1\frdmk66f_freertos_hello\board" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-freertos_kernel-2f-portable-2f-GCC-2f-ARM_CM4F

clean-freertos-2f-freertos_kernel-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.d ./freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.o

.PHONY: clean-freertos-2f-freertos_kernel-2f-portable-2f-GCC-2f-ARM_CM4F

