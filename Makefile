CXX = g++

CXXFLAGS = -std=c++0x -g -I./inc
LIBS = -L./lib -lglfw3 -lpthread -lGL -lXxf86vm -lXrandr -lXcursor -lXi -lX11 -lXinerama

OUT_EXE = HW2

all: $(OUT_EXE)

$(OUT_EXE): main.o hw2.o glwrapper.o Obj_Tool.o Mesh_Tool.o
	$(CXX) $^ $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o $(OUT_EXE)
