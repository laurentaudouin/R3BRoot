##############################################################################
#   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    #
#   Copyright (C) 2019 Members of R3B Collaboration                          #
#                                                                            #
#             This software is distributed under the terms of the            #
#                 GNU General Public Licence (GPL) version 3,                #
#                    copied verbatim in the file "LICENSE".                  #
#                                                                            #
# In applying this license GSI does not waive the privileges and immunities  #
# granted to it by virtue of its status as an Intergovernmental Organization #
# or submit itself to any jurisdiction.                                      #
##############################################################################

cmake_minimum_required(VERSION 3.0)

enable_testing()
set(PROJECT_TEST_NAME NeulandUnitTests)
set(GTEST_ROOT ${SIMPATH})
find_package(GTest REQUIRED)

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/neuland/test/*.cxx)

include_directories(${GTEST_INCLUDE_DIRS}
                    ${SYSTEM_INCLUDE_DIRECTORIES}
                    ${BASE_INCLUDE_DIRECTORIES}
                    ${R3BROOT_SOURCE_DIR}/r3bbase
                    ${R3BROOT_SOURCE_DIR}/r3bdata/neulandData
                    ${R3BROOT_SOURCE_DIR}/neuland/shared
                    ${R3BROOT_SOURCE_DIR}/neuland/reconstruction)

link_directories(${GTEST_LIBS_DIR}
                 ${ROOT_LIBRARY_DIR}
                 ${FAIRROOT_LIBRARY_DIR}
                 ${Boost_LIBRARY_DIRS})

set(TEST_DEPENDENCIES
    ${GTEST_BOTH_LIBRARIES}
    ${ROOT_LIBRARIES}
    FairLogger::FairLogger
    FairTools
    R3Bbase
    R3BData
    R3BNeulandShared
    R3BNeulandReconstruction)

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
target_link_libraries(${PROJECT_TEST_NAME} ${TEST_DEPENDENCIES})
add_test(${PROJECT_TEST_NAME} ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_TEST_NAME})

generate_root_test_script(${R3BROOT_SOURCE_DIR}/neuland/test/testNeulandSimulation.C)
add_test(NeulandSimulation ${R3BROOT_BINARY_DIR}/neuland/test/testNeulandSimulation.sh)
set_tests_properties(NeulandSimulation PROPERTIES TIMEOUT "2000")
set_tests_properties(NeulandSimulation
                     PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully.")

generate_root_test_script(${R3BROOT_SOURCE_DIR}/neuland/test/testNeulandDigitizer.C)
add_test(NeulandDigitizer ${R3BROOT_BINARY_DIR}/neuland/test/testNeulandDigitizer.sh)
set_tests_properties(NeulandDigitizer PROPERTIES DEPENDS NeulandSimulation)
set_tests_properties(NeulandDigitizer PROPERTIES TIMEOUT "1000")
set_tests_properties(NeulandDigitizer
                     PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully.")

add_subdirectory(calibration)
