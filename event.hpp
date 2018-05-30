#ifndef __PW_EVENT_HPP__
#define __PW_EVENT_HPP__

#include <list>
#include "delegate.hpp"

namespace pw
{

    template <typename... _Params>
    class event
    {

    public:

        template<void(*_Function)(_Params...)>
        void add()
        {
            m_delegates.emplace_back();
            auto &delegate = m_delegates.back();
            delegate.bind<_Function>();
        }

        template <class _ObjectType, void(_ObjectType::*_Function)(_Params...)>
        void add(_ObjectType *_object)
        {
            m_delegates.emplace_back();
            auto &delegate = m_delegates.back();
            delegate.bind<_ObjectType, _Function>(_object);
        }

        template<void(*_Function)(_Params...)>
        void remove()
        {
            delegate<void, _Params...> remove_delegate;
            remove_delegate.bind<_Function>();
            m_delegates.remove(remove_delegate);
        }

        template <class _ObjectType, void(_ObjectType::*_Function)(_Params...)>
        void remove(_ObjectType *_object)
        {
            delegate<void, _Params...> remove_delegate;
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
            return this->invoke(_params...);
        }

    private:

        std::list<delegate<void, _Params...>> m_delegates;
    };

} // namespace pw

#endif // end of include guard
