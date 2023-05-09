################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dspi.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_ftm.c \
../drivers/fsl_fxos.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_rtc.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dspi.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_ftm.d \
./drivers/fsl_fxos.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_rtc.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dspi.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_ftm.o \
./drivers/fsl_fxos.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_rtc.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\drivers" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\device" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\utilities" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\component\uart" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\component\serial_manager" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\component\lists" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\CMSIS" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\freertos\freertos_kernel\include" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\board" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\source" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\drivers" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\device" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\utilities" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\component\uart" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\component\serial_manager" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\component\lists" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\CMSIS" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\freertos\freertos_kernel\include" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\board" -I"C:\Users\dengr6\Desktop\project\frdmk66f_freertos_hello\source" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dspi.d ./drivers/fsl_dspi.o ./drivers/fsl_ftfx_cache.d ./drivers/fsl_ftfx_cache.o ./drivers/fsl_ftfx_controller.d ./drivers/fsl_ftfx_controller.o ./drivers/fsl_ftfx_flash.d ./drivers/fsl_ftfx_flash.o ./drivers/fsl_ftfx_flexnvm.d ./drivers/fsl_ftfx_flexnvm.o ./drivers/fsl_ftm.d ./drivers/fsl_ftm.o ./drivers/fsl_fxos.d ./drivers/fsl_fxos.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2c.d ./drivers/fsl_i2c.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_rtc.d ./drivers/fsl_rtc.o ./drivers/fsl_smc.d ./drivers/fsl_smc.o ./drivers/fsl_uart.d ./drivers/fsl_uart.o

.PHONY: clean-drivers

