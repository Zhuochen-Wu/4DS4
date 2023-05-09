################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_OS_BAREMETAL -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\drivers" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\accel" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\utilities" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\device" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\component\uart" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\component\lists" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\CMSIS" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\board" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\source" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\drivers" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\accel" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\utilities" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\device" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\component\uart" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\component\lists" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\CMSIS" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\board" -I"C:\Users\wuz147\Desktop\lab1-problem4B\frdmk66f_bubble_peripheral\frdmk66f\demo_apps\bubble_peripheral" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/peripherals.d ./board/peripherals.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

