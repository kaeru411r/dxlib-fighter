#pragma once
#if false
namespace ike {


    class EnableSharedFromThis { 
    public:
        using _Esft_type = EnableSharedFromThis;

        [[nodiscard]] std::shared_ptr< shared_from_this() {
            return shared_ptr<_Ty>(_Wptr);
        }

        _NODISCARD shared_ptr<const _Ty> shared_from_this() const {
            return shared_ptr<const _Ty>(_Wptr);
        }

        _NODISCARD weak_ptr<_Ty> weak_from_this() noexcept {
            return _Wptr;
        }

        _NODISCARD weak_ptr<const _Ty> weak_from_this() const noexcept {
            return _Wptr;
        }

    protected:
        constexpr enable_shared_from_this() noexcept : _Wptr() {}

        enable_shared_from_this(const enable_shared_from_this&) noexcept : _Wptr() {
            // construct (must value-initialize _Wptr)
        }

        enable_shared_from_this& operator=(const enable_shared_from_this&) noexcept { // assign (must not change _Wptr)
            return *this;
        }

        ~enable_shared_from_this() = default;

    private:
        template <class _Yty>
        friend class shared_ptr;

        mutable weak_ptr<_Ty> _Wptr;
    };




}

#endif