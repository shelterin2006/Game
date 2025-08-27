cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Game)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# Our Project

# =============================================================================
# SỬ DỤNG HÀM TÙY CHỈNH
# =============================================================================

# Thay vì gọi add_executable(...)
# hãy gọi hàm tùy chỉnh của chúng ta: project_add_executable(...)
enable_testing()
add_executable(${PROJECT_NAME}
        Source/main.cpp
        Source/game_objects/character/character.h
        Source/cards/card.h
        Source/scenes/mainMenu.cpp
        Source/scenes/mainMenu.h
        Source/utils/gamedefs.h
        Source/scenes/credits.cpp
        Source/scenes/credits.h
        Source/scenes/pickCard.cpp
        Source/scenes/pickCard.h
        Source/core/Resource.cpp
        Source/core/Resource.h
        Source/core/scene.cpp
        Source/core/scene.h
        Source/scenes/battleScene.cpp
        Source/scenes/battleScene.h
        Source/game_objects/actions/IAction.h
        Source/game_objects/actions/DamageAction.h
        Source/cards/DeckManager.h
        Source/cards/DeckManager.cpp
        Source/game_objects/actions/IAction.h
        Source/core/Animation.h
        Source/scenes/ChoseChar.cpp
        Source/scenes/ChoseChar.h
        Source/game_objects/character/CharacterManager.h
        Source/utils/Params.h
        Source/game_objects/actions/HealAction.h
        Source/cards/card.cpp
        Source/game_objects/character/CharacterManager.cpp
)
add_test(NAME RunGameTest COMMAND ${PROJECT_NAME})

# Đặt thư mục làm việc cho test case "RunGameTest"
# Đây là phần sẽ được CLion và các công cụ khác tôn trọng
set_property(
        TEST RunGameTest
        PROPERTY WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Post-build command for Game: Copy executable to Release directory
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/Release" # Create Release directory if not exists
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:Game>" "${CMAKE_SOURCE_DIR}/Release/" # Copy .exe file
    COMMENT "Copying Game.exe to ${CMAKE_SOURCE_DIR}/Release"
)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()