CXX = g++
CXXFLAGS =  -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
 			-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported \
  			-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
   			-Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual \
    		-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
	 		-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods \
	  		-Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef \
	   		-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix \
	    	-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector \
		 	-fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging \
		  	-fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
			-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
TARGET = main
SourcePrefix = src/
BuildPrefix = build/
BuildFolder = build
Include = -Iinclude -IColor_console_output/include

Sources = InputOutput.cpp Sorts.cpp Error.cpp
Main = main.cpp

LibObjects = Color_console_output/build/Color_output.o

Source = $(addprefix $(SourcePrefix), $(Sources))
MainObject = $(patsubst %.cpp, $(BuildPrefix)%.o, $(Main))

objects = $(patsubst $(SourcePrefix)%.cpp, $(BuildPrefix)%.o, $(Source))

.PHONY : all clean folder lib

all : lib

lib: CXXFLAGS = -O3
lib: folder prepare $(objects) $(LibObjects)
	cd build && ar -rc libOnegin_task.a *.o ../Color_console_output/build/*.o 

prepare : 
	cd Color_console_output && make

$(BuildPrefix)%.o : $(SourcePrefix)%.cpp
	cd Color_console_output && make

	@echo [CXX] -c $< -o $@
	@$(CXX) $(CXXFLAGS) $(Include) -c $< -o $@


$(TARGET) : $(objects) $(MainObject) $(LibObjects)
	@echo [CC] $^ -o $@
	@$(CXX) $(CXXFLAGS) $(Include) $^ -o $@

clean :
	rm $(BuildFolder)/*.o
	rm $(BuildFolder)/*.a
	cd Color_console_output && make clean

folder :
	mkdir -p $(BuildFolder)