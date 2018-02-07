BIN_DIR  = ./bin
SRC_DIR  = ./src

ifdef CXX # CXX defined in environment
  CPP = $(CXX)
  CC = $(CXX)
else
  CPP = g++
endif

ifeq ($(CPP), clang++)
  GCC_FLAGS=-O3 -std=c++11 -stdlib=libc++ 
endif

HEADERS	= $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp src/*/*.cpp)

AGG_INCLUDE_PATH = -I/usr/include/agg2/
LIBS += -lagg

ifdef DEBUG
  CPPFLAGS += -g $(GCC_FLAGS) -isystem/$(AGG_INCLUDE_PATH) -Isrc
else
  # release mode
  CPPFLAGS += -DNDEBUG $(GCC_FLAGS) $(AGG_INCLUDE_PATH) -Isrc
endif

# all
OBJS = $(SOURCES:.cpp=.o)

OUTPUT = $(BIN_DIR)/Ninjaplot

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) $(LIBS) -o $(OUTPUT)

$(OBJS): $(HEADERS)

.SUFFIXES : .cpp .c .o $(SUFFIXES)

clean:
	rm -vf $(SRC_DIR)/*.o
	rm -vf $(SRC_DIR)/*/*.o
