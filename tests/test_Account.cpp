#include <Account.h>
#include <gtest/gtest.h>

TEST(Account, Banking){
//создаём тестовый объект
	Account test(0,0);
//проверяем GetBalance (и заодно конструктор)
	ASSERT_EQ(test.GetBalance(), 0);
//проверяем, что фича lock работает нормально
	ASSERT_THROW(test.ChangeBalance(100), std::runtime_error);
	test.Lock();
	ASSERT_NO_THROW(test.ChangeBalance(100));
//проверяем, что изменение баланса работает
	ASSERT_EQ(test.GetBalance(), 100);
//проверяем, что залочить уже залоченное нельзя
	ASSERT_THROW(test.Lock(), std::runtime_error);
//проверяем, что анлок работает
	test.Unlock();
	ASSERT_THROW(test.ChangeBalance(100), std::runtime_error);
//радуемся жизни
}
