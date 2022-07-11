#include "gtest/gtest.h"
#include "discord-ipc/serialization/activity_flags.h"
#include <nlohmann/json.hpp>

using namespace discord_ipc::types;

TEST(serialization_activity_flags, func_has_int) {
	activity_flags activity_flags(1);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_TRUE(activity_flags.has(1));
	ASSERT_FALSE(activity_flags.has(2));
	ASSERT_FALSE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(4));
}
TEST(serialization_activity_flags, func_has_int1) {
	activity_flags activity_flags(2);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_FALSE(activity_flags.has(1));
	ASSERT_TRUE(activity_flags.has(2));
	ASSERT_FALSE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(4));
}
TEST(serialization_activity_flags, func_has_int2) {
	activity_flags activity_flags(3);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_TRUE(activity_flags.has(1));
	ASSERT_TRUE(activity_flags.has(2));
	ASSERT_TRUE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(4));
}

TEST(serialization_activity_flags, func_has_flag) {
	activity_flags activity_flags(activity_flags::instance);
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_TRUE(activity_flags.has(activity_flags::instance));
	ASSERT_FALSE(activity_flags.has(activity_flags::join));
	ASSERT_FALSE(activity_flags.has(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get()));
	ASSERT_FALSE(activity_flags.has(activity_flags::spectate));
}
TEST(serialization_activity_flags, func_has_flag1) {
	activity_flags activity_flags(activity_flags::join);
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_FALSE(activity_flags.has(activity_flags::instance));
	ASSERT_TRUE(activity_flags.has(activity_flags::join));
	ASSERT_FALSE(activity_flags.has(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get()));
	ASSERT_FALSE(activity_flags.has(activity_flags::spectate));
}
TEST(serialization_activity_flags, func_has_flag2) {
	activity_flags activity_flags(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get());
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_TRUE(activity_flags.has(activity_flags::instance));
	ASSERT_TRUE(activity_flags.has(activity_flags::join));
	ASSERT_TRUE(activity_flags.has(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get()));
	ASSERT_FALSE(activity_flags.has(activity_flags::spectate));
}

TEST(serialization_activity_flags, func_add_int) {
	activity_flags activity_flags(0);
	activity_flags.add(1);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_TRUE(activity_flags.has(1));
	ASSERT_FALSE(activity_flags.has(2));
	ASSERT_FALSE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(4));
}
TEST(serialization_activity_flags, func_add_int1) {
	activity_flags activity_flags(1);
	activity_flags.add(2);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_TRUE(activity_flags.has(1));
	ASSERT_TRUE(activity_flags.has(2));
	ASSERT_TRUE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(4));
}

TEST(serialization_activity_flags, func_add_flag) {
	activity_flags activity_flags(activity_flags::none);
	activity_flags.add(activity_flags::instance);
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_TRUE(activity_flags.has(activity_flags::instance));
	ASSERT_FALSE(activity_flags.has(activity_flags::join));
	ASSERT_FALSE(activity_flags.has(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get()));
	ASSERT_FALSE(activity_flags.has(activity_flags::spectate));
}
TEST(serialization_activity_flags, func_add_flag1) {
	activity_flags activity_flags(activity_flags::instance);
	activity_flags.add(activity_flags::join);
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_TRUE(activity_flags.has(activity_flags::instance));
	ASSERT_TRUE(activity_flags.has(activity_flags::join));
	ASSERT_TRUE(activity_flags.has(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get()));
	ASSERT_FALSE(activity_flags.has(activity_flags::spectate));
}

TEST(serialization_activity_flags, func_remove_int) {
	activity_flags activity_flags(3);
	activity_flags.remove(1);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_FALSE(activity_flags.has(1));
	ASSERT_TRUE(activity_flags.has(2));
	ASSERT_FALSE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(4));
}
TEST(serialization_activity_flags, func_remove_int1) {
	activity_flags activity_flags(4);
	activity_flags.remove(2);
	ASSERT_TRUE(activity_flags.has(0));
	ASSERT_FALSE(activity_flags.has(1));
	ASSERT_FALSE(activity_flags.has(2));
	ASSERT_FALSE(activity_flags.has(3));
	ASSERT_TRUE(activity_flags.has(4));
}

TEST(serialization_activity_flags, func_remove_flag) {
	activity_flags activity_flags(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get());
	activity_flags.remove(activity_flags::instance);
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_FALSE(activity_flags.has(activity_flags::instance));
	ASSERT_TRUE(activity_flags.has(activity_flags::join));
	ASSERT_FALSE(activity_flags.has(3));
	ASSERT_FALSE(activity_flags.has(activity_flags::spectate));
}
TEST(serialization_activity_flags, func_remove_flag1) {
	activity_flags activity_flags(activity_flags::spectate);
	activity_flags.remove(activity_flags::join);
	ASSERT_TRUE(activity_flags.has(activity_flags::none));
	ASSERT_FALSE(activity_flags.has(activity_flags::instance));
	ASSERT_FALSE(activity_flags.has(activity_flags::join));
	ASSERT_FALSE(activity_flags.has(activity_flag(activity_flags::instance).get() + activity_flag(activity_flags::join).get()));
	ASSERT_TRUE(activity_flags.has(activity_flags::spectate));
}