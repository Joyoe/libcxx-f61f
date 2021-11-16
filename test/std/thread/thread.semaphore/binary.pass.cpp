//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads
// UNSUPPORTED: c++98, c++03, c++11

// This test requires the dylib support introduced in D68480
// XFAIL: with_system_cxx_lib=macosx10.15
// XFAIL: with_system_cxx_lib=macosx10.14
// XFAIL: with_system_cxx_lib=macosx10.13
// XFAIL: with_system_cxx_lib=macosx10.12
// XFAIL: with_system_cxx_lib=macosx10.11
// XFAIL: with_system_cxx_lib=macosx10.10
// XFAIL: with_system_cxx_lib=macosx10.9

// <semaphore>

#include <semaphore>
#include <chrono>
#include <thread>

#include "test_macros.h"

int main(int, char**)
{
  std::binary_semaphore s(1);

  auto l = [&](){
    for(int i = 0; i < 1024; ++i) {
        s.acquire();
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        s.release();
    }
  };

  std::thread t(l);
  l();

  t.join();

  return 0;
}
