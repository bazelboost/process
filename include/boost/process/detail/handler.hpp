// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_HANDLER_HPP_

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {

//extended handler base.
typedef api::handler_base_ext handler;


template <class Handler>
struct on_setup_ : handler
{
    explicit on_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_setup(Executor &e) const
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_error_ : handler
{
    explicit on_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_success_ : handler
{
    explicit on_success_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_success(Executor &e) const
    {
        handler_(e);
    }
private:
    Handler handler_;
};

}

constexpr boost::process::detail::make_handler_t<boost::process::detail::on_setup_>   on_setup;
constexpr boost::process::detail::make_handler_t<boost::process::detail::on_error_>   on_error;
constexpr boost::process::detail::make_handler_t<boost::process::detail::on_success_> on_success;


}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */