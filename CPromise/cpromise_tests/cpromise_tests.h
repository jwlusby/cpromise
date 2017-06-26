// cpromise_tests.h : Unit tests for cpromise library
//
#ifndef _CPROMISE_TESTS_H
#define _CPROMISE_TESTS_H

#include <stdint.h>
#include <stdbool.h>
#include "../cpromise/cpromise.h"

#ifdef __cplusplus
extern "C" {
#endif




	void test_Execute_CPromise_Suite();

	void test_CanInitializeAndDisposePromiseManager();
	void test_CanProcessWithEmptyList();
	void test_CanAddAPromise();

	///////////////////////////////////////////////////////////
	typedef struct test_CanProcessAPromise_State {
		int count;
	}test_CanProcessAPromise_State;
	PromiseState test_CanProcessAPromise_Process(void* _state);
	void test_CanProcessAPromise_Dispose(void* _state);
	void test_CanProcessAPromise();

	///////////////////////////////////////////////////////////
	typedef struct test_CanResolveAPromise_State {
		int count;
		bool* success;
	}test_CanResolveAPromise_State;
	PromiseState test_CanResolveAPromise_Process(void* _state);
	void test_CanResolveAPromise_Resolve(void* _state);
	void test_CanResolveAPromise_Dispose(void* _state);
	void test_CanResolveAPromise();

	///////////////////////////////////////////////////////////
	typedef struct test_CanRejectAPromise_State {
		int count;
		bool* resolveCalled;
		bool* rejectCalled;
	}test_CanRejectAPromise_State;
	PromiseState test_CanRejectAPromise_Process(void* _state);
	void test_CanRejectAPromise_Resolve(void* _state);
	void test_CanRejectAPromise_Reject(void* _state);
	void test_CanRejectAPromise_Dispose(void* _state);
	void test_CanRejectAPromise();

	///////////////////////////////////////////////////////////
	typedef struct test_CanDisposeAPromiseAfterRejected_State {
		int count;
		bool* resolveCalled;
		bool* rejectCalled;
		bool* disposeCalled;
	}test_CanDisposeAPromiseAfterRejected_State;
	PromiseState test_CanDisposeAPromiseAfterRejected_Process(void* _state);
	void test_CanDisposeAPromiseAfterRejected_Resolve(void* _state);
	void test_CanDisposeAPromiseAfterRejected_Reject(void* _state);
	void test_CanDisposeAPromiseAfterRejected_Dispose(void* _state);
	void test_CanDisposeAPromiseAfterRejected();

	///////////////////////////////////////////////////////////
	typedef struct test_CanDisposeAPromiseAfterResolved_State {
		int count;
		bool* resolveCalled;
		bool* rejectCalled;
		bool* disposeCalled;
	}test_CanDisposeAPromiseAfterResolved_State;
	PromiseState test_CanDisposeAPromiseAfterResolved_Process(void* _state);
	void test_CanDisposeAPromiseAfterResolved_Resolve(void* _state);
	void test_CanDisposeAPromiseAfterResolved_Reject(void* _state);
	void test_CanDisposeAPromiseAfterResolved_Dispose(void* _state);
	void test_CanDisposeAPromiseAfterResolved();


#ifdef __cplusplus
}
#endif

#endif