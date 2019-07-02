#all:lib target_bin target_hex clean burn
#.PHONY:lib target_bin clean burn #target_hex

########################
# Target
#######################
TARGET:=FRTOS_T1

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build
STLINK:=/usr/local/Cellar/stlink/1.5.1/bin

######################################
# source
######################################
# C sources
C_SOURCES = \
User/main.c \
User/stm32f4xx_it.c \
User/system_stm32f4xx.c \
bsp/bsp.c \
bsp/src/bsp_uart_fifo.c \
bsp/src/bsp_tim_pwm.c \
bsp/printf.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c

# ASM sources
#ASRC_DIR:=$(wildcadr $(STARTUP)/*.s)
	#@echo $(ASRC_DIR)

ASM_SOURCES = \
startup_stm32f446xx.s

#FRTOS_ASM_SOURCES =
	#@echo $(ASRC)

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DSTM32F446xx


# AS includes
AS_INCLUDES =

# C includes
C_INCLUDES =  \
-IUser \
-Ibsp \
-Ibsp/inc \
-ILibraries/CMSIS/Device/ST/STM32F4xx/Include \
-ILibraries/CMSIS/Include \
-ILibraries/STM32F4xx_StdPeriph_Driver/inc \
-IFreeRTOS/include \
-IFreeRTOS/portable/GCC/ARM_CM4F

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

burn:$(TARGET).bin
	$(STLINK)/st-flash write $(TARGET).bin 0x8000000

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)