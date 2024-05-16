# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ESoPePlatformExample)

# The following line is needed when creating eso files in the format of ESoPe GmbH. For this you need the Flasher tool of ESoPe GmbH.
# This is needed to use the secure software update mechanisms implemented from ESoPe.
#add_custom_target(${PROJECT_NAME} ALL COMMAND "$ENV{FLASHERDIR}\\Flasher.Cli.exe" "${project_dir}/config.json")
#add_dependencies(${PROJECT_NAME} gen_project_binary)