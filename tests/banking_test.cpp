#include "Account.h"
#include "Transaction.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount() : Account(1, 100000) {}

    MockAccount(int id, int balance) : Account(id, balance) {}

    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    MOCK_METHOD(int, id, ());
};

class MockTransaction : public Transaction {
public:
    MOCK_METHOD(bool, Make, (Account & from, Account & to, int sum));
    MOCK_METHOD(int, fee, ());
    MOCK_METHOD(void, set_fee, (int fee));
};

class AccountTest : public ::testing::Test {
protected:
    Account acc;
};

class TransactionTest : public ::testing::Test {
protected:
    Transaction transaction;
};

TEST_F(AccountTest, Lock) {
    EXPECT_NO_THROW(acc.Lock());
    ASSERT_THROW(acc.Lock(), std::runtime_error);
}

TEST_F(AccountTest, Unlock) {
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
    acc.Unlock();
    ASSERT_NO_THROW(acc.Lock());
}

TEST_F(AccountTest, GetBalance) {
    ASSERT_EQ(acc.GetBalance(), 100000);
}

TEST_F(AccountTest, ChangeBalance) {
    EXPECT_THROW(acc.ChangeBalance(50000), std::runtime_error);
    acc.Lock();
    EXPECT_NO_THROW(acc.ChangeBalance(50000));
    EXPECT_EQ(acc.GetBalance(), 150000);
}

TEST(mockAccountTest, mockTest) {
    using testing::Return;

    MockAccount acc(1, 100000);

    EXPECT_CALL(acc, id()).WillOnce(Return(1));
    EXPECT_CALL(acc, GetBalance())
            .WillOnce(Return(50000))
            .WillOnce(Return(100000));
    EXPECT_CALL(acc, ChangeBalance(50000)).Times(1);
    EXPECT_CALL(acc, Lock()).Times(1);
    EXPECT_CALL(acc, Unlock()).Times(1);

    acc.id();
    acc.GetBalance();
    acc.ChangeBalance(50000);
    acc.GetBalance();
    acc.Lock();
    acc.Unlock();
}

TEST_F(TransactionTest, fee) {
    ASSERT_EQ(transaction.fee(), 1);
}

TEST_F(TransactionTest, set_fee) {
    transaction.set_fee(20);
    ASSERT_EQ(transaction.fee(), 20);
}

TEST_F(TransactionTest, Make) {
    using ::testing::_;
    using ::testing::Return;

    Account acc1(1, 500000);
    Account acc2(2, 450000);
    transaction.set_fee(100);

    EXPECT_THROW(transaction.Make(acc1, acc1, 100000), std::logic_error);
    EXPECT_THROW(transaction.Make(acc1, acc2, -100000), std::invalid_argument);
    EXPECT_THROW(transaction.Make(acc1, acc2, 50), std::logic_error);

    EXPECT_FALSE(transaction.Make(acc1, acc2, 100));
    EXPECT_FALSE(transaction.Make(acc1, acc2, 600000));

    EXPECT_TRUE(transaction.Make(acc1, acc2, 100000));
    EXPECT_EQ(acc1.GetBalance(), 399900);
    EXPECT_EQ(acc2.GetBalance(), 550000);

    MockTransaction mockTransaction;
    MockAccount mockAcc1(1, 500000);
    MockAccount mockAcc2(2, 450000);
}

TEST(mockTransaction, mockTest) {
    using testing::_;
    using testing::Return;

    MockTransaction transaction;
    MockAccount acc1(1, 500000);
    MockAccount acc2(2, 400000);

    EXPECT_CALL(transaction, fee())
            .WillOnce(Return(1))
            .WillOnce(Return(100));
    EXPECT_CALL(transaction, set_fee(_)).Times(1);
    EXPECT_CALL(transaction, Make(_, _, _)).Times(1);

    transaction.fee();
    transaction.set_fee(100);
    transaction.fee();
    transaction.Make(acc1, acc2, 100000);
}
