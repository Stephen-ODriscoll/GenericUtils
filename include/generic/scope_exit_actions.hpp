/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <stack>
#include <functional>

namespace Generic
{
    class scope_exit_actions
    {
        std::stack<std::function<void()>> m_actions{};

    public:
        scope_exit_actions() {}

        scope_exit_actions(const std::function<void()>& action)
        {
            add(action);
        }

        ~scope_exit_actions()
        {
            for (; !m_actions.empty(); m_actions.pop())
            {
                const auto& action{ m_actions.top() };

                if (action)
                {
                    try
                    {
                        action();
                    }
                    catch (...) {}
                }
            }
        }

        void add(const std::function<void()>& action)
        {
            m_actions.push(action);
        }
    };
}
