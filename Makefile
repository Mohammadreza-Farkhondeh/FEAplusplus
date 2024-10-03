BUILD_DIR = build
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release

all: configure build

configure:
	@echo "Configuring project..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS) ..

build:
	@echo "Building project..."
	@cmake --build $(BUILD_DIR)

test:
	@echo "Running tests..."
	@cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

rebuild: clean all

install:
	@echo "Installing project..."
	@cd $(BUILD_DIR) && make install

.PHONY: all configure build test clean rebuild install

