################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Controller.cpp \
../Object.cpp \
../TodoCattlefarm.cpp \
../TodoCow.cpp \
../TodoEmployee.cpp \
../TodoFarmer.cpp \
../TodoFarmland.cpp \
../TodoFeeder.cpp \
../TodoProperty.cpp \
../TodoScene.cpp \
../View.cpp \
../main.cpp \
../test.cpp 

OBJS += \
./Controller.o \
./Object.o \
./TodoCattlefarm.o \
./TodoCow.o \
./TodoEmployee.o \
./TodoFarmer.o \
./TodoFarmland.o \
./TodoFeeder.o \
./TodoProperty.o \
./TodoScene.o \
./View.o \
./main.o \
./test.o 

CPP_DEPS += \
./Controller.d \
./Object.d \
./TodoCattlefarm.d \
./TodoCow.d \
./TodoEmployee.d \
./TodoFarmer.d \
./TodoFarmland.d \
./TodoFeeder.d \
./TodoProperty.d \
./TodoScene.d \
./View.d \
./main.d \
./test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -static -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


