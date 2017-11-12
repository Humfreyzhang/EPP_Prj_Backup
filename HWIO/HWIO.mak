SUBDIRS += HWIO/
SUBDIRS += HWIO/DeviceDriver/
SUBDIRS += HWIO/Interface/
SUBDIRS += HWIO/OS/
SUBDIRS += HWIO/Cald/
SUBDIRS += HWIO/Hal/

INCDIRS += HWIO/OS/
INCDIRS += HWIO/Include/
INCDIRS += HWIO/IO_Config/
INCDIRS += HWIO/Interface/
INCDIRS += HWIO/Cald/
INCDIRS += HWIO/Hal/


include $(HOME_DIR)/HWIO/Communication/Communication.mak
MAKFILE_DEPENDS += $(HOME_DIR)/HWIO/HWIO.mak