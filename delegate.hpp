#ifndef __PW_DELEGATE_HPP__
#define __PW_DELEGATE_HPP__

namespace pw
{

    template <typename _ReturnType, typename... _Params>
    class delegate
    {

    private:

        typedef void* object_type;
        typedef _ReturnType(*function_type)(object_type, _Params...);

    public:

        delegate() :
            m_object(nullptr),
            m_function(nullptr)
        {
        }

        template<_ReturnType(*_Function)(_Params...)>
        void bind()
        {
            m_object = nullptr;
            m_function = &function_stub<_Function>;
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...)>
        void bind(_ObjectType *_object)
        {
            m_object = _object;
            m_function = &function_stub<_ObjectType, _Function>;
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void bind(_ObjectType *_object)
        {
            m_object = _object;
            m_function = &function_stub<_ObjectType, _Function>;
        }

        _ReturnType invoke(_Params... _params) const
        {
            return m_function(m_object, _params...);
        }

        _ReturnType operator()(_Params... _params) const
        {
            return this->invoke(_params...);
        }

        bool operator==(const delegate& _other) const
        {
            return (m_object == _other.m_object) && (m_function == _other.m_function);
        }

        bool operator!= (const delegate& _other) const
        {
            return !(*this == _other);
        }

    private:

        object_type m_object;
        function_type m_function;

    private:

        // turns a free function into internal function stub
        template <_ReturnType(*_Function)(_Params...)>
        static _ReturnType function_stub(object_type _instance, _Params... _params)
        {
            // we don't need the instance pointer because we're dealing with free functions
            return (_Function)(_params...);
        }

        // turns a member function into internal function stub
        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...)>
        static _ReturnType function_stub(object_type _instance, _Params... _params)
        {
            // cast the instance pointer back into the original class instance
            return (static_cast<_ObjectType*>(_instance)->*_Function)(_params...);
        }

        // turns a const member function into internal function stub
        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        static _ReturnType function_stub(object_type _instance, _Params... _params)
        {
            // cast the instance pointer back into the original class instance
            return (static_cast<_ObjectType*>(_instance)->*_Function)(_params...);
        }
    };

    // specialization for const functions
    template <typename _ReturnType, typename... _Params>
    class const_delegate
    {

    private:

        typedef void const* object_type;
        typedef _ReturnType(*function_type)(object_type, _Params...);

    public:

        const_delegate() :
            m_object(nullptr),
            m_function(nullptr)
        {
        }

        template<_ReturnType(*_Function)(_Params...)>
        void bind()
        {
            m_object = nullptr;
            m_function = &function_stub<_Function>;
        }

        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        void bind(_ObjectType *const _object)
        {
            m_object = _object;
            m_function = &function_stub<_ObjectType, _Function>;
        }

        _ReturnType invoke(_Params... _params) const
        {
            return m_function(m_callee, _params...);
        }

        _ReturnType operator()(_Params... _params) const
        {
            return this->invoke(_params...);
        }

        bool operator==(const const_delegate& _other) const
        {
            return (m_object == _other.m_object) && (m_function == other.m_function);
        }

        bool operator!= (const const_delegate& _other) const
        {
            return !(*this == other);
        }

    private:

        object_type m_object;
        function_type m_function;

    private:

        // turns a free function into internal function stub
        template <_ReturnType(*_Function)(_Params...)>
        static _ReturnType function_stub(object_type _instance, _Params... _params)
        {
            // we don't need the instance pointer because we're dealing with free functions
            return (_Function)(_params...);
        }

        // turns a const member function into internal function stub
        template <class _ObjectType, _ReturnType(_ObjectType::*_Function)(_Params...) const>
        static _ReturnType function_stub(object_type _instance, _Params... _params)
        {
            // cast the instance pointer back into the original class instance
            return (static_cast<_ObjectType const*>(_instance)->*_Function)(_params...);
        }
    };

} // namespace pw

#endif // end of include guard
