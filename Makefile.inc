APPL_COBJS += balancer.o balancer_param.o 

APPL_CXXOBJS += driver.o lineMonitor.o colorMonitor.o tracer.o calibration.o Pid.o mileage.o basicCourseR.o armControler.o changeEdge.o etzumo.o straightRunner.o Logger.o revolver.o blockErea.o returnLine.o status.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif
