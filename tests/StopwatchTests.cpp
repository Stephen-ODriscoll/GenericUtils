/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/stopwatch.hpp"

#include <gtest/gtest.h>

#include <thread>

class StopwatchTests : public testing::Test
{
protected:
    StopwatchTests() {}
    ~StopwatchTests() {}
};

// Basic sanity, timings are difficult to test
TEST_F(StopwatchTests, TestSeconds)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(stopwatch.in_seconds(), 1);
    ASSERT_EQ(stopwatch.seconds_part(), 1);
}

TEST_F(StopwatchTests, TestCopyConstructor)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    Generic::stopwatch stopwatch2{ stopwatch };
    ASSERT_EQ(stopwatch.time(), stopwatch2.time());
}

TEST_F(StopwatchTests, TestTimeCallDoesNotStop)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_NE(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopCallStaysStopped)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallStaysStopped)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopCallOnStoppedNoChange)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallOnStoppedNoChange)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStartCallDoesNotRestart)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.start();
    auto secondTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestRestartCallDoesRestart)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.restart();
    auto secondTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(StopwatchTests, TestStopCallAndStartCallDoesNotRestart)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallAndStartCallDoesNotRestart)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.is_running());

    auto secondTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestStopCallAndRestartCallDoesRestart)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallAndRestartCallDoesRestart)
{
    Generic::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.is_running());

    auto secondTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(secondTime < firstTime);
}
