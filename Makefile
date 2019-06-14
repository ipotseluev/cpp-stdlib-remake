SRC=$(shell pwd)/source
HEADERS=$(shell pwd)/include
BUILD=$(shell pwd)/build
GXX=g++
GXX_OBJ_FLAGS='-std=c++17'

all: directories test

.PHONY directories: $(BUILD)
$(BUILD):
	mkdir -p $(BUILD)

#------------INSTALL
DEV_INSTALL=/opt/include/igor
DEV_DIR=include 

install: install_dirs $(DEV_INSTALL)/shared_ptr.h $(DEV_INSTALL)/shared_ptr-inl.h

$(DEV_INSTALL)/shared_ptr.h: $(DEV_DIR)/shared_ptr.h
	sudo install $<  $@

$(DEV_INSTALL)/shared_ptr-inl.h: $(DEV_DIR)/shared_ptr-inl.h 
	sudo install $<  $@

$(DEV_INSTALL)/make_shared.h: $(DEV_DIR)/make_shared.h 
	sudo install $<  $@

.PHONY install_dirs: $(DEV_INSTALL)
$(DEV_INSTALL):
	sudo mkdir -p $@

#-------------all_tests
test: test_directories std_test my_test run_test
BUILD_TESTS=$(shell pwd)/build/tests

.PHONY test_directories: $(BUILD_TESTS)
$(BUILD_TESTS):
	mkdir -p $(BUILD_TESTS)

run_test: std_test
	@echo "\n---------------------------------------------------------------------"
	@echo "STD tests:"
	$(BUILD_TESTS)/std-simple-test
	@echo "\n---------------------------------------------------------------------"
	@echo "MY tests:"
	$(BUILD_TESTS)/my-simple-test

#-------------std_tests
std_test: $(BUILD_TESTS)/std-simple-test
TEST_STD_SHARED_PTR=$(shell pwd)/tests/std/utils/smart_ptr

$(BUILD_TESTS)/std-simple-test: $(TEST_STD_SHARED_PTR)/simple-test.cpp
	$(GXX) -std=c++11 $< -o $@


#-------------my_tests
TEST_MY_SHARED_PTR=$(shell pwd)/tests/my/utils/smart_ptr
# for some reason it should be re-decleared
DEV_DIR=include

my_test: $(BUILD_TESTS)/my-simple-test 
$(BUILD_TESTS)/my-simple-test: $(TEST_MY_SHARED_PTR)/simple-test.cpp $(DEV_DIR)/shared_ptr.h $(DEV_DIR)/shared_ptr-inl.h

	$(GXX) $(GXX_OBJ_FLAGS) -I $(DEV_DIR) $< -o $@


#-------------CLEAN
.PHONY: clean distclean
clean:
	rm -rf $(BUILD) $(BUILD_TESTS)

distclean:
	rm -rf $(DEV_INSTALL)
