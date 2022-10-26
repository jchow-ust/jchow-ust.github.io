################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp \
../organization.cpp \
../regionx.cpp \
../regiony.cpp \
../who.cpp 

OBJS += \
./main.o \
./organization.o \
./regionx.o \
./regiony.o \
./who.o 

CPP_DEPS += \
./main.d \
./organization.d \
./regionx.d \
./regiony.d \
./who.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


