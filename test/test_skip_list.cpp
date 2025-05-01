#include "Skip_List.h"
#include <gtest.h>

class skip_list_test : public ::testing::Test {
protected:
	void SetUp() {
		list = new SkipList(3);

		list->insert(23);		//
		list->insert(12);		//
		list->insert(45);		// 
		list->insert(5);		// [5] -> [12] -> [23] -> [45]
	}
	void TearDown() {
		delete list;
	}

	SkipList* list;
};


TEST_F(skip_list_test, create_skip_list) {
	ASSERT_NO_THROW(this->SetUp());
};
TEST_F(skip_list_test, max_level_skip_list) {
	this->SetUp();
	EXPECT_EQ(this->list->get_maxLevel(), 3);
}
TEST_F(skip_list_test, find_skip_list_correct) {
	this->SetUp();
	EXPECT_EQ(this->list->find(23)->key, 23);
}
TEST_F(skip_list_test, find_skip_list_ancorrect) {
	this->SetUp();
	EXPECT_EQ(this->list->find(24), nullptr);
}
TEST_F(skip_list_test, insert_skip_list) {
	this->SetUp();
	EXPECT_EQ(this->list->find(65), nullptr);
	this->list->insert(65);
}
TEST_F(skip_list_test, erase_skip_list_correct) {
	this->SetUp();
	this->list->erase(23);
	EXPECT_EQ(this->list->find(23), nullptr);
}
TEST_F(skip_list_test, throw_erase_skip_list_ancorrect) {
	this->SetUp();
	ASSERT_ANY_THROW(this->list->erase(100));
}
TEST_F(skip_list_test, save_sorted_skip_list) {
	this->SetUp();
	EXPECT_EQ(this->list->find(12)->next->key, 23);
	//[12] -> [23]
}
TEST_F(skip_list_test, down_pointer_is_nullptr_skip_list) {
	this->SetUp();
	EXPECT_EQ(this->list->find(12)->down, nullptr);
}