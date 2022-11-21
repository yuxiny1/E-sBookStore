//copyright (c) 2020 by Chrono 

#ifndef _ZMQ_HPP
#define _ZMQ_HPP

#include "cpplang.hpp"

// /usr/include/zmq.hpp
#include <zmq.hpp>

BEGIN_NAMESPACE(esbookshop)

using zmq_context_type = zmq::context_t;// 
using zmq_socket_type  = zmq::socket_t; // socket is a class in zmq.hpp
using zmq_message_type = zmq::message_t;

template<int thread_num=1>
class ZmqContext final 
{
    #if 0
    public:
        using zmq_context_type = zmq::context_t;// alias
        using zmq_socket_type = zmq::socket_t; // alias
        using zmq_message_type = zmq::message_t;

    #endif
    public:
        ZmqContext() = default;
        ~ZmqContext() = default;
    public:
        static
        zmq_context_type& context()
        {
            static zmq_context_type ctx(thread_num);// thread safe
            return ctx;
        }
    public:
        static
        zmq_context_type& context()
        {
            static zmq_context_type ctx(thread_num);// thread safe
            return ctx;
        }
    public:

        static
        zmq_socket_type& recv_sock(int hwm=1000, int linger=10)// high water mark , linger is the time to wait for the message to be received 
        {
            zmq_socket_type sock(context(), ZMQ_PULL);

            sock.setsockopt(ZMQ_RCVHWM, hwm);
            sock.setsockopt(ZMQ_LINGER, linger);

            return sock;
        }
        static
        zmq_socket_type& send_sock(int hwm=1000, int linger=10)
        //
        {
            zmq_socket_type sock(context(), ZMQ_PUSH);

            sock.setsockopt(ZMQ_SNDHWM, hwm);
            sock.setsockopt(ZMQ_LINGER, linger);

            return sock;
        }

END_NAMESPACE(esbookshop)
#endif
        
