cmake_minimum_required(VERSION 3.16)
project(WebS)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-pthread")

add_executable(WebS 
		WebS.cpp
        CountDownLatch.h
        CountDownLatch.cpp
        Mutex.h
        nocopyable.h
        Thread.cpp
        Thread.h
        ThreadPool.cpp
        ThreadPool.h
        Atomic.h
        BlockQueue.h
        Condition.h
        buffer.cpp
        httpresponse.h
        httpresponse.cpp
        httprequest.cpp
        httprequest.h
        httpconn.cpp
        httpconn.h
        buffer.h
        heaptimer.h
        heaptimer.cpp
        epoller.h
        epoller.cpp
        webserver.h
        webserver.cpp
        )
