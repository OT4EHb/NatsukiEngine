#pragma once
#include<thread>

#include <Natsuki.hpp>

class NATSUKI ThreadPool {
private:
	std::thread *pool;
public:
	ThreadPool(unsigned size = std::thread::hardware_concurrency()) {
		pool = new std::thread[size];
	}
	~ThreadPool() {
		delete pool;
	}
	std::thread operator[](unsigned i) const {
		return pool[i];
	}
};