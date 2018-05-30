#ifndef __PW_EVENT_HPP__
#define __PW_EVENT_HPP__

#include <list>
#include "delegate.hpp"

namespace pw
{

    template <typename>
    class event;

    template <typename>
    class const_event;

    template <typename _ReturnType, typename... _Params>
    class event<_ReturnType(_Params...)>
    {

    public:

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
            delegate<_ReturnType(_Params...)> remove_delegate;
            remove_delegate.bind<_Function>();
            m_delegates.remove(remove_delegate);
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...)>
        void remove(_ObjectType *_object)
        {
            delegate<_ReturnType(_Params...)> remove_delegate;
            remove_delegate.bind<_ObjectType, _Function>(_object);
            m_delegates.remove(remove_delegate);
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void remove(_ObjectType *_object)
        {
            delegate<_ReturnType(_Params...)> remove_delegate;
            remove_delegate.bind<_ObjectType, _Function>(_object);
            m_delegates.remove(remove_delegate);
        }

        void invoke(_Params... _params) const
        {
            for (auto &delegate : m_delegates)
            {
                delegate.invoke(_params...);
            }
        }

        void operator()(_Params... _params) const
        {
            this->invoke(_params...);
        }

    private:

        std::list<delegate<_ReturnType(_Params...)>> m_delegates;
    };

    template <typename _ReturnType, typename... _Params>
    class const_event<_ReturnType(_Params...)>
    {

    public:

        void add(const_delegate<_ReturnType(_Params...)> &_delegate)
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

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void add(_ObjectType *_object)
        {
            m_delegates.emplace_back();
            auto &delegate = m_delegates.back();
            delegate.bind<_ObjectType, _Function>(_object);
        }

        void remove(const_delegate<_ReturnType(_Params...)> &_delegate)
        {
            m_delegates.remove(_delegate);
        }

        template<_ReturnType(*_Function)(_Params...)>
        void remove()
        {
            const_delegate<_ReturnType(_Params...)> remove_delegate;
            remove_delegate.bind<_Function>();
            m_delegates.remove(remove_delegate);
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void remove(_ObjectType *_object)
        {
            const_delegate<_ReturnType(_Params...)> remove_delegate;
            remove_delegate.bind<_ObjectType, _Function>(_object);
            m_delegates.remove(remove_delegate);
        }

        void invoke(_Params... _params) const
        {
            for (auto &delegate : m_delegates)
            {
                delegate.invoke(_params...);
            }
        }

        void operator()(_Params... _params) const
        {
            this->invoke(_params...);
        }

    private:

        std::list<const_delegate<_ReturnType(_Params...)>> m_delegates;
    };

} // namespace pw

#endif // end of include guard
