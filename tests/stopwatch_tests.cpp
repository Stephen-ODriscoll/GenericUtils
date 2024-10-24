/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/stopwatch.hpp"

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
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_EQ(stopwatch.inSeconds(), 1);
    ASSERT_EQ(stopwatch.secondsPart(), 1);
}

TEST_F(StopwatchTests, TestCopyConstructor)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.isRunning());

    pluto::Stopwatch stopwatch2{ stopwatch };
    ASSERT_EQ(stopwatch.time(), stopwatch2.time());
}

TEST_F(StopwatchTests, TestTimeCallDoesNotStop)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_NE(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopCallStaysStopped)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallStaysStopped)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    auto firstTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopCallOnStoppedNoChange)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallOnStoppedNoChange)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    auto firstTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStartCallDoesNotRestart)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.start();
    auto secondTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.isRunning());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestRestartCallDoesRestart)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.restart();
    auto secondTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.isRunning());

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(StopwatchTests, TestStopCallAndStartCallDoesNotRestart)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallAndStartCallDoesNotRestart)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.isRunning());

    auto secondTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestStopCallAndRestartCallDoesRestart)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.isRunning());

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(StopwatchTests, TestStopAndTimeCallAndRestartCallDoesRestart)
{
    pluto::Stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.isRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.isRunning());

    auto secondTime{ stopwatch.stopAndTime() };
    ASSERT_FALSE(stopwatch.isRunning());

    ASSERT_TRUE(secondTime < firstTime);
}
