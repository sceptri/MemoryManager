TEMPLATE = subdirs

SUBDIRS = \
	MemoryManager

MemoryManager.subdir = MemoryManager

OTHER_FILES += GCC_OLD/sources/*.cpp \
    GCC_OLD/headers/*.h

debug: message(Hello)
message(There)

CONFIG(Debug) { message(Yep) }

message(CONFIG)
