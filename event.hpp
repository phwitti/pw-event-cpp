#ifndef __PW_EVENT_HPP__
#define __PW_EVENT_HPP__

#include <functional>
#include <list>
#include "delegate.hpp"

namespace pw
{

    template <typename>
    class event;

    template <typename _ReturnType, typename... _Params>
    class event<_ReturnType(_Params...)>
    {

    public:

        template<typename... _FunctionParams>
        void add(_FunctionParams&&... _params)
        {
            m_functions.emplace_back(std::forward<_FunctionParams>(_params)...);
        }

        void add(delegate<_ReturnType(_Params...)> &_delegate)
        {
            m_delegates.push_back(_delegate);
        }

        template<_ReturnType(*_Function)(_Params...)>
        void add()
        {
            m_delegates.emplace_back();
            auto &delegate = m_delegates.back();
            delegate.bind<_Function>();
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...)>
        void add(_ObjectType *_object)
        {
            m_delegates.emplace_back();
            auto &delegate = m_delegates.back();
            delegate.bind<_ObjectType, _Function>(_object);
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void add(_ObjectType *_object)
        {
            m_delegates.emplace_back();
            auto &delegate = m_delegates.back();
            delegate.bind<_ObjectType, _Function>(_object);
        }

        void remove(delegate<_ReturnType(_Params...)> &_delegate)
        {
            m_delegates.remove(_delegate);
        }

        template<_ReturnType(*_Function)(_Params...)>
        void remove()
        {
            m_delegates.remove(delegate<_ReturnType(_Params...)>::create<_Function>());
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...)>
        void remove(_ObjectType *_object)
        {
            m_delegates.remove(delegate<_ReturnType(_Params...)>::create<_ObjectType, _Function>(_object));
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void remove(_ObjectType *_object)
        {
            m_delegates.remove(delegate<_ReturnType(_Params...)>::create<_ObjectType, _Function>(_object));
        }

        void invoke(_Params... _params) const
        {
            for (auto &delegate : m_delegates)
            {
                delegate.invoke(_params...);
            }

            for (auto &function : m_functions)
            {
                function(_params...);
            }
        }

        void operator()(_Params... _params) const
        {
            this->invoke(_params...);
        }

    private:

        std::list<delegate<_ReturnType(_Params...)>> m_delegates;
        std::list<std::function<_ReturnType(_Params...)>> m_functions;
    };

} // namespace pw

#endif // end of include guard
