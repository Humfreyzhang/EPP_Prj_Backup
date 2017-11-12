# Define all C source files (dependencies are generated automatically)
SUBDIRS ?= App/
#SUBDIRS += App/UDS/source
SUBDIRS += App/OS_TASK/
SUBDIRS += App/App_cald/
SUBDIRS += App/Motor_Control/
SUBDIRS += App/CAN_Matrix/
SUBDIRS += App/IOMM/
SUBDIRS += App/DGDM/
SUBDIRS += App/EPP_Moduel/
export SUBDIRS

INCDIRS ?= App/include
#INCDIRS += App/UDS/include
INCDIRS += App/OS_TASK/
INCDIRS += App/App_cald/
INCDIRS += App/Motor_Control/
INCDIRS += App/CAN_Matrix/
INCDIRS += App/DataType/
INCDIRS += App/IOMM/
INCDIRS += App/DGDM/
INCDIRS += App/EPP_Moduel/
export INCDIRS

MAKFILE_DEPENDS += $(HOME_DIR)/App/App.mak