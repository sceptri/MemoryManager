TEMPLATE = app

HEADERS += \
    ../src/headers/complex.h \
    ../src/headers/memorymanager.h

INCLUDEPATH += \
    "../src/headers" \

SOURCES += \
    ../src/sources/main.cpp \
    ../src/sources/complex.cpp \
    ../src/sources/memorymanager.cpp \


CONFIG(debug, debug|release) {
	DESTDIR = /home/sceptri/Dev/QtWorkspace/MemoryManager/bin/Debug-linux-x86_64
	MOC_DIR = "../bin-int/Debug-linux-x86_64"
	RCC_DIR = "../bin-int/Debug-linux-x86_64"
	UI_DIR = "../bin-int/Debug-linux-x86_64"
	CONFIG += \
		console \
}

CONFIG(release, debug|release) {
	DESTDIR = /home/sceptri/Dev/QtWorkspace/MemoryManager/bin/Release-linux-x86_64
	MOC_DIR = "../bin-int/Release-linux-x86_64"
	RCC_DIR = "../bin-int/Release-linux-x86_64"
	UI_DIR = "../bin-int/Release-linux-x86_64"
	CONFIG += \
		console \
}

unix:DEFINES += USE_MEMORY_MANAGER
