/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <stack>
#include <functional>

namespace pluto
{
    class ScopeExitActions
    {
        std::stack<std::function<void()>> m_actions{};

    public:
        ScopeExitActions() {}

        ScopeExitActions(const std::function<void()>& action)
        {
            add(action);
        }

        ~ScopeExitActions()
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
