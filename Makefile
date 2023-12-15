ifdef WINDOWS
DSONAME = SOP_Merge.dll
else ifdef MBSD
DSONAME = SOP_Merge.dylib
else
DSONAME = SOP_Merge.so
endif

# List of C++ source files to build.
SOURCES = \
	SOP_Merge.C \
# Additional include directories.
INCDIRS = \
        -I$(HFS)/toolkit/include \
        

include $(HFS)/toolkit/makefiles/Makefile.gnu
