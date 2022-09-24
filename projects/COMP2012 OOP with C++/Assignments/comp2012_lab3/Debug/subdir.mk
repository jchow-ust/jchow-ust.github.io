################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Coronavirus.cpp \
../Doctor.cpp \
../Norovirus.cpp \
../Patient.cpp \
../Patient_with_coronavirus.cpp \
../Patient_with_norovirus.cpp \
../Person.cpp \
../Virus.cpp \
../main.cpp 

OBJS += \
./Coronavirus.o \
./Doctor.o \
./Norovirus.o \
./Patient.o \
./Patient_with_coronavirus.o \
./Patient_with_norovirus.o \
./Person.o \
./Virus.o \
./main.o 

CPP_DEPS += \
./Coronavirus.d \
./Doctor.d \
./Norovirus.d \
./Patient.d \
./Patient_with_coronavirus.d \
./Patient_with_norovirus.d \
./Person.d \
./Virus.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


