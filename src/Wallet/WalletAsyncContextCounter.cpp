// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2017-2018 The Circle Foundation & Conceal Devs
// Copyright (c) 2018-2019 Conceal Network & Conceal Devs
// Copyright (c) 2019-2020 The Wallet 2 Wallet Team
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletAsyncContextCounter.h"

namespace CryptoNote {

void WalletAsyncContextCounter::addAsyncContext() {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_asyncContexts++;
}

void WalletAsyncContextCounter::delAsyncContext() {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_asyncContexts--;

  if (!m_asyncContexts) m_cv.notify_one();
}

void WalletAsyncContextCounter::waitAsyncContextsFinish() {
  std::unique_lock<std::mutex> lock(m_mutex);
  while (m_asyncContexts > 0)
    m_cv.wait(lock);
}

} //namespace CryptoNote
