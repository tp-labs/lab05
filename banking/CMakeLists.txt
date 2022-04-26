cmake_minimum_required(VERSION 3.16.3)
project(Bank)

add_library(
	banking STATIC
		Account.cpp
		Account.h
		Transaction.cpp
		Transaction.h
)

set_target_properties(
	banking PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED oN
)
