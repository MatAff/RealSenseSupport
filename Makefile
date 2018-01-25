
# Specify folder structure here or use . for current folder
HDR_DIR = .
SRC_DIR = .
OBJ_DIR = .

# Specify all file containing main (these should be ignored initially)
IGNORE := $(SRC_DIR)/Dev.cpp 

# All files to compile
CC_FILES := $(filter-out $(IGNORE), $(wildcard $(SRC_DIR)/*.cpp))

# All object file
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CC_FILES))

# All target (files containing main method)
TARGETS = Dev
DEFAULT_TGT = Dev

CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -fPIC -Wall # -pg
CVINC = -I/usr/local/lib
CVLIBS = -L/usr/local/lib -lopencv_highgui -lopencv_core -lopencv_imgproc -lrealsense2
INC = -I$(HDR_DIR) $(CVINC)
LDFLAGS = $(CVLIBS) -lrealsense2

all: $(DEFAULT_TGT)

everything: $(TARGETS)

# Link
Dev: $(OBJ_FILES)
	$(CC) $(OPT) $(DEBUG) $(CFLAGS) $(INC) $(SRC_DIR)/$@.cpp -o $@ $^ $(LDFLAGS)

# Compile
(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(OPT) $(DEBUG) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(TARGETS) ./$(OBJ_DIR)/*.o

