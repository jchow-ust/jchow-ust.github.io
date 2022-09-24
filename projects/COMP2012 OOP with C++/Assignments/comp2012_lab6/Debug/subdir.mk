################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Customer.cpp \
../Invoice.cpp \
../Person.cpp \
../Product.cpp \
../Salesman.cpp \
../main.cpp 

OBJS += \
./Customer.o \
./Invoice.o \
./Person.o \
./Product.o \
./Salesman.o \
./main.o 

CPP_DEPS += \
./Customer.d \
./Invoice.d \
./Person.d \
./Product.d \
./Salesman.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


