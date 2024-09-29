cmake_minimum_required(VERSION 3.12.4)

# 添加 FreeType 查找
find_package(Freetype REQUIRED)

# 将 FreeType 的包含路径添加到编译器选项
include_directories(${FREETYPE_INCLUDE_DIRS})

# 将 FreeType 库链接到你的目标
# 假设你有一个可执行文件或库需要链接，替换 `your_target` 为实际的目标名称
target_link_libraries(your_target PRIVATE ${FREETYPE_LIBRARIES})

if(NOT ESP_PLATFORM)
  project(lvgl HOMEPAGE_URL https://github.com/lvgl/lvgl)
endif()

set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

if(ESP_PLATFORM)
  include(${CMAKE_CURRENT_LIST_DIR}/env_support/cmake/esp.cmake)
elseif(ZEPHYR_BASE)
  include(${CMAKE_CURRENT_LIST_DIR}/env_support/cmake/zephyr.cmake)
elseif(MICROPY_DIR)
  include(${CMAKE_CURRENT_LIST_DIR}/env_support/cmake/micropython.cmake)
else()
  include(${CMAKE_CURRENT_LIST_DIR}/env_support/cmake/custom.cmake)
endif()
