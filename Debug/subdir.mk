################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../01Window.cpp \
../02Triangle.cpp \
../03Shaders1.cpp \
../03Shaders2.cpp \
../04Texture.cpp \
../05Transformation.cpp \
../06Camera.cpp \
../GLcamera.cpp \
../GLobject.cpp \
../GLshader.cpp \
../main.cpp 

OBJS += \
./01Window.o \
./02Triangle.o \
./03Shaders1.o \
./03Shaders2.o \
./04Texture.o \
./05Transformation.o \
./06Camera.o \
./GLcamera.o \
./GLobject.o \
./GLshader.o \
./main.o 

CPP_DEPS += \
./01Window.d \
./02Triangle.d \
./03Shaders1.d \
./03Shaders2.d \
./04Texture.d \
./05Transformation.d \
./06Camera.d \
./GLcamera.d \
./GLobject.d \
./GLshader.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


