#include <Transaction.h>
#include <Account.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using::testing::Return;
using::testing::AtLeast;
using::testing::NiceMock;

class MockAccount: public Account{
public:
    MockAccount(int id, int balance):Account(id, balance){}
    MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction: public Transaction{
public:
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(Account, InitGetChange){
    NiceMock<MockAccount> n(184953, 500);
    EXPECT_EQ(n.Account::GetBalance(), 500);
    EXPECT_THROW(n.Account::ChangeBalance(100), std::runtime_error);
    n.Account::Lock();
    EXPECT_THROW(n.Account::Lock(), std::runtime_error);
    n.Account::ChangeBalance(100);
    EXPECT_EQ(n.Account::GetBalance(), 600);
}
TEST(Account, Unlock){
    NiceMock<MockAccount> n(184953, 500);
    EXPECT_CALL(n, Unlock()).Times(1);
    n.Unlock();
}
TEST(Transaction, Saving){
    NiceMock<MockAccount> n(184953, 500);
    NiceMock<MockAccount> m(184954, 200);
    MockTransaction l;
    EXPECT_CALL(l, SaveToDataBase(n, m, 300)).Times(1);
    l.SaveToDataBase(n, m, 300);
}
