#ifndef _TYPE_SWITCH_H_
#define _TYPE_SWITCH_H_

#include <utility>

namespace impl
{

	template <typename... Fs>
	struct overload_t;

	template <typename F, typename... Fs>
	struct overload_t<F, Fs...> : F, overload_t<Fs...>::type
	{
		typedef overload_t type;

		overload_t(F&& f, Fs&&... fs)
			: F(std::move(f)), overload_t<Fs...>::type(std::move(fs)...)
		{}

		using F::operator();
		using overload_t<Fs...>::type::operator();
	};

	template <typename F>
	struct overload_t<F> : F
	{
		typedef F type;
		using F::operator();
	};

	template <typename F>
	struct otherwise_t : F
	{
		otherwise_t(F&& f) : F(std::move(f)) {}

		template <typename U>
		void operator()(U&&) const { F::operator()(); }
	};

	template <typename T>
	class matcher_t
	{
		typedef T&& TRef;
		TRef t_;
	public:
		matcher_t(TRef t) : t_(std::forward<T>(t)) {}

		template <typename... Fs>
		void operator()(Fs&&... fs)
		{
			overload_t<Fs...>(std::forward<Fs>(fs)...)(std::forward<T>(t_));
		}
	};
}

template <typename... Fs>
typename impl::overload_t<Fs...>::type overload(Fs&&... fs)
{
	return impl::overload_t<Fs...>(std::forward<Fs>(fs)...);
}

template <typename T>
impl::matcher_t<T> match(T&& t)
{
	return impl::matcher_t<T>(std::forward<T>(t));
}

template <typename F>
impl::otherwise_t<F> otherwise(F&& f)
{
	return impl::otherwise_t<F>(std::forward<F>(f));
}

#endif
