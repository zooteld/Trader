// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2014-2016 SDN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <mutex>
#include <condition_variable>

#pragma once

class EventWaiter {
private:
  std::mutex mtx;
  std::condition_variable cv;
  bool available;

public:
  EventWaiter() : available(false) {}

  void notify();
  void wait();
  bool wait_for(const std::chrono::milliseconds& rel_time);
};
