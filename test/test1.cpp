#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include <Transaction.h>
#include <Account.h>


class MockAccount: public Account{
public:
    MockAccount(int id, int balance):Account(id, balance){}
    MOCK_METHOD0(void, Unlock, ());
};
TEST(Account, Init){
    MockAccount test(1,100);
    EXPECT_EQ(test.GetBalance(),100);
    EXPECT_EQ(test.id(),1);
}

class MockTransaction: public Transaction{
public:
    MOCK_METHOD3(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(Account, GetBalance){
MockAccount acc(1,100);
EXPECT_EQ(acc.Account::GetBalance(), 100);
}

TEST(Account, ChangeBalance){
MockAccount acc(0, 100);
EXPECT_THROW(acc.Account::ChangeBalance(50), std::runtime_error);
acc.Account::Lock();
acc.Account::ChangeBalance(50);
EXPECT_EQ(acc.Account::GetBalance(), 150);

}

TEST(Account, Lock) {
    MockAccount acc(15,213);
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(Account, Unlock){
    MockAccount acc(0, 100);
EXPECT_CALL(acc, Unlock()).Times(1);
acc.Unlock();
}

TEST(Transaction, Make){
MockAccount from_acc(15,17650);
MockAccount to_acc(13, 18435);
MockTransaction tr;
EXPECT_THROW(tr.Make(from_acc,from_acc,0),std::logic_error);
EXPECT_THROW(tr.Make(from_acc,to_acc,0),std::logic_error);
EXPECT_THROW(tr.Make(from_acc,to_acc,-5),std::invalid_argument);
}

TEST(Transaction, SaveToDataBase){
MockAccount from_acc(15,17650);
MockAccount to_acc(13, 18435);
MockTransaction tr;


}