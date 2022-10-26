################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../beverage_store.cpp \
../gold_card.cpp \
../main.cpp \
../regular_card.cpp \
../sliver_card.cpp \
../vip_lounge.cpp 

OBJS += \
./beverage_store.o \
./gold_card.o \
./main.o \
./regular_card.o \
./sliver_card.o \
./vip_lounge.o 

CPP_DEPS += \
./beverage_store.d \
./gold_card.d \
./main.d \
./regular_card.d \
./sliver_card.d \
./vip_lounge.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


