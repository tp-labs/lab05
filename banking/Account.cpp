#include "Account.h"

#include <stdexcept>

Account::Account(int id, int balance)
    : id_(id), balance_(balance), is_locked_(false) {}

Account::~Account() {}

int Account::GetBalance() const { return balance_; }

void Account::ChangeBalance(int diff) {
  if (!is_locked_) throw std::runtime_error("at first lock the account");
  balance_ += diff;
}

void Account::Lock() {
  if (is_locked_) throw std::runtime_error("already locked");
  is_locked_ = true;
}

void Account::Unlock() { is_locked_ = false; }
