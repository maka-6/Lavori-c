# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-src"
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-build"
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix"
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/makao/OneDrive/Desktop/Lav/esercitazioni/Lavori-c/Clion Raylib/Disegni di Mondrian/src/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
