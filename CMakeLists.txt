# CMakeLists.txt для Fake Trainer
# Альтернативный способ сборки через CMake

cmake_minimum_required(VERSION 3.15)
project(FakeTrainer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ImGui source files
set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_win32.cpp
    imgui_impl_dx11.cpp
)

# Main executable
add_executable(trainer WIN32
    main.cpp
    ${IMGUI_SOURCES}
)

# Link DirectX11
target_link_libraries(trainer PRIVATE
    d3d11
    d3dcompiler
)

# Include current directory for ImGui headers
target_include_directories(trainer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Release optimizations
if(MSVC)
    # Size optimization flags
    target_compile_options(trainer PRIVATE
        $<$<CONFIG:Release>:/O1>        # Minimize size
        $<$<CONFIG:Release>:/Os>        # Favor small code
        $<$<CONFIG:Release>:/MD>        # Multi-threaded DLL runtime
        $<$<CONFIG:Release>:/GS->       # Disable security checks
        $<$<CONFIG:Release>:/GR->       # Disable RTTI
    )
    
    # Linker optimizations
    target_link_options(trainer PRIVATE
        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
        $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>
        $<$<CONFIG:Release>:/OPT:REF>
        $<$<CONFIG:Release>:/OPT:ICF>
        $<$<CONFIG:Release>:/LTCG>
        $<$<CONFIG:Release>:/MANIFEST:NO>
    )
    
    # Enable link-time code generation
    set_property(TARGET trainer PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()

# Post-build: strip and compress (optional, requires tools in PATH)
# Uncomment if you have strip.exe and upx.exe in PATH:
# add_custom_command(TARGET trainer POST_BUILD
#     COMMAND strip $<TARGET_FILE:trainer>
#     COMMAND upx --best --lzma $<TARGET_FILE:trainer>
#     COMMENT "Stripping and compressing executable..."
# )

message(STATUS "==================================================")
message(STATUS "Build configuration:")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "==================================================")
message(STATUS "After build, run manually:")
message(STATUS "  strip trainer.exe")
message(STATUS "  upx --best --lzma trainer.exe")
message(STATUS "==================================================")
