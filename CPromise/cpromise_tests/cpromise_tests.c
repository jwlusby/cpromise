// CPromise.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "cpromise_tests.h"


#ifdef __cplusplus
extern "C" {
#endif

	void test_Execute_CPromise_Suite() {
		test_CanInitializeAndDisposePromiseManager();
		test_CanProcessWithEmptyList();
		test_CanAddAPromise();
		test_CanProcessAPromise();
		test_CanResolveAPromise();
		test_CanRejectAPromise();
		test_CanDisposeAPromiseAfterRejected();
		test_CanDisposeAPromiseAfterResolved();
	}

	///////////////////////////////////////////////
	//<test_CanInitializeAndDisposePromiseManager>
	void test_CanInitializeAndDisposePromiseManager() {
		PromiseManager* promiseManager = PromiseManager_New();
		promiseManager->Dispose(promiseManager);

		printf("[PASS] test_CanInitializeAndDisposePromiseManager\r\n");
	}
	//</test_CanInitializeAndDisposePromiseManager>
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//<test_CanProcessWithEmptyList>
	void test_CanProcessWithEmptyList() {
		PromiseManager* promiseManager = PromiseManager_New();
		promiseManager->Process(promiseManager);
		promiseManager->Dispose(promiseManager);

		printf("[PASS] test_CanProcessWithEmptyList\r\n");
	}
	//</test_CanProcessWithEmptyList>
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//<test_CanAddAPromise>
	void test_CanAddAPromise() {
		PromiseManager* promiseManager = PromiseManager_New();
		promiseManager->AddPromise(promiseManager, NULL, NULL, NULL, NULL, NULL);
		promiseManager->Dispose(promiseManager);

		printf("[PASS] test_CanAddAPromise\r\n");
	}
	//</test_CanAddAPromise>
	///////////////////////////////////////////////


	///////////////////////////////////////////////
	//<test_CanProcessAPromise_State>
	PromiseState test_CanProcessAPromise_Process(void* _state) {
		struct test_CanProcessAPromise_State* state = (struct test_CanProcessAPromise_State*)_state;
		if (state->count == 100) {
			return RESOLVED;
		}
		else {
			state->count++;
		}
	}

	void test_CanProcessAPromise_Dispose(void* _state) {
		struct test_CanProcessAPromise_State* state = (struct test_CanProcessAPromise_State*)_state;
		free(state);
	}

	void test_CanProcessAPromise() {
		PromiseManager* promiseManager = PromiseManager_New();
		struct test_CanProcessAPromise_State* state = (struct test_CanProcessAPromise_State*)malloc(sizeof(test_CanProcessAPromise_State));
		state->count = 0;

		promiseManager->AddPromise(promiseManager, (void*)state, test_CanProcessAPromise_Process, NULL, NULL, test_CanProcessAPromise_Dispose);
		while (promiseManager->Count > 0) {
			promiseManager->Process(promiseManager);
		}
		promiseManager->Dispose(promiseManager);

		printf("[PASS] test_CanProcessAPromise\r\n");
	}
	//</test_CanProcessAPromise_State>
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//<test_CanResolveAPromise_State>
	PromiseState test_CanResolveAPromise_Process(void* _state) {
		struct test_CanResolveAPromise_State* state = (struct test_CanResolveAPromise_State*)_state;
		if (state->count == 100) {
			return RESOLVED;
		}
		else {
			state->count++;
		}
	}

	void test_CanResolveAPromise_Resolve(void* _state) {
		struct test_CanResolveAPromise_State* state = (struct test_CanResolveAPromise_State*)_state;
		(*state->success) = true;
		return;
	}

	void test_CanResolveAPromise_Dispose(void* _state) {
		struct test_CanResolveAPromise_State* state = (struct test_CanResolveAPromise_State*)_state;
		free(state);
	}

	void test_CanResolveAPromise() {
		bool success = false;
		PromiseManager* promiseManager = PromiseManager_New();
		struct test_CanResolveAPromise_State* state = (struct test_CanResolveAPromise_State*)malloc(sizeof(test_CanResolveAPromise_State));
		state->count = 0;
		state->success = &success;

		promiseManager->AddPromise(promiseManager, (void*)state, test_CanResolveAPromise_Process, test_CanResolveAPromise_Resolve, NULL, test_CanResolveAPromise_Dispose);
		while (promiseManager->Count > 0) {
			promiseManager->Process(promiseManager);
		}
		if (state->success) {
			printf("[PASS] test_CanResolveAPromise\r\n");
		}
		else {
			printf("[FAIL] test_CanResolveAPromise\r\n");
		}
		promiseManager->Dispose(promiseManager);
	}
	//</test_CanResolveAPromise_State>
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//<test_CanRejectAPromise_State>
	PromiseState test_CanRejectAPromise_Process(void* _state) {
		struct test_CanRejectAPromise_State* state = (struct test_CanRejectAPromise_State*)_state;
		if (state->count == 100) {
			return RESOLVED;
		}
		else if (state->count == 50) {
			return REJECTED;
		}
		else {
			state->count++;
		}
	}

	void test_CanRejectAPromise_Resolve(void* _state) {
		struct test_CanRejectAPromise_State* state = (struct test_CanRejectAPromise_State*)_state;
		(*state->resolveCalled) = true;
		return;
	}

	void test_CanRejectAPromise_Reject(void* _state) {
		struct test_CanRejectAPromise_State* state = (struct test_CanRejectAPromise_State*)_state;
		(*state->rejectCalled) = true;
		return;
	}

	void test_CanRejectAPromise_Dispose(void* _state) {
		struct test_CanRejectAPromise_State* state = (struct test_CanRejectAPromise_State*)_state;
		free(state);
	}

	void test_CanRejectAPromise() {
		bool resolveCalled = false;
		bool rejectCalled = false;
		PromiseManager* promiseManager = PromiseManager_New();
		struct test_CanRejectAPromise_State* state = (struct test_CanRejectAPromise_State*)malloc(sizeof(test_CanRejectAPromise_State));
		state->count = 0;
		state->resolveCalled = &resolveCalled;
		state->rejectCalled = &rejectCalled;

		promiseManager->AddPromise(promiseManager, (void*)state, test_CanRejectAPromise_Process, test_CanRejectAPromise_Resolve, test_CanRejectAPromise_Reject, test_CanRejectAPromise_Dispose);
		while (promiseManager->Count > 0) {
			promiseManager->Process(promiseManager);
		}
		if ((!resolveCalled) && rejectCalled) {
			printf("[PASS] test_CanRejectAPromise\r\n");
		}
		else {
			printf("[FAIL] test_CanRejectAPromise\r\n");
		}
		promiseManager->Dispose(promiseManager);
	}
	//</test_CanRejectAPromise_State>
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//<test_CanDisposeAPromiseAfterRejected
	PromiseState test_CanDisposeAPromiseAfterRejected_Process(void* _state) {
		struct test_CanDisposeAPromiseAfterRejected_State* state = (struct test_CanDisposeAPromiseAfterRejected_State*)_state;
		if (state->count == 100) {
			return RESOLVED;
		}
		else if (state->count == 50) {
			return REJECTED;
		}
		else {
			state->count++;
		}
	}

	void test_CanDisposeAPromiseAfterRejected_Resolve(void* _state) {
		struct test_CanDisposeAPromiseAfterRejected_State* state = (struct test_CanDisposeAPromiseAfterRejected_State*)_state;
		(*state->resolveCalled) = true;
		return;
	}

	void test_CanDisposeAPromiseAfterRejected_Reject(void* _state) {
		struct test_CanDisposeAPromiseAfterRejected_State* state = (struct test_CanDisposeAPromiseAfterRejected_State*)_state;
		(*state->rejectCalled) = true;
		return;
	}

	void test_CanDisposeAPromiseAfterRejected_Dispose(void* _state) {
		struct test_CanDisposeAPromiseAfterRejected_State* state = (struct test_CanDisposeAPromiseAfterRejected_State*)_state;
		(*state->disposeCalled) = true;
		return;
	}

	void test_CanDisposeAPromiseAfterRejected() {
		bool resolveCalled = false;
		bool rejectCalled = false;
		bool disposeCalled = false;
		PromiseManager* promiseManager = PromiseManager_New();
		struct test_CanDisposeAPromiseAfterRejected_State* state = (struct test_CanDisposeAPromiseAfterRejected_State*)malloc(sizeof(test_CanDisposeAPromiseAfterRejected_State));
		state->count = 0;
		state->resolveCalled = &resolveCalled;
		state->rejectCalled = &rejectCalled;
		state->disposeCalled = &disposeCalled;

		promiseManager->AddPromise(promiseManager, (void*)state, test_CanDisposeAPromiseAfterRejected_Process, test_CanDisposeAPromiseAfterRejected_Resolve, test_CanDisposeAPromiseAfterRejected_Reject, test_CanDisposeAPromiseAfterRejected_Dispose);
		while (promiseManager->Count > 0) {
			promiseManager->Process(promiseManager);
		}
		if (rejectCalled && disposeCalled) {
			printf("[PASS] test_CanDisposeAPromiseAfterRejected\r\n");
		}
		else {
			printf("[FAIL] test_CanDisposeAPromiseAfterRejected\r\n");
		}
		promiseManager->Dispose(promiseManager);
	}
	//</test_CanDisposeAPromiseAfterRejected>
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	//<test_CanDisposeAPromiseAfterResolved>
	PromiseState test_CanDisposeAPromiseAfterResolved_Process(void* _state) {
		struct test_CanDisposeAPromiseAfterResolved_State* state = (struct test_CanDisposeAPromiseAfterResolved_State*)_state;
		if (state->count == 100) {
			return RESOLVED;
		}
		else if (state->count > 100) {
			return REJECTED;
		}
		else {
			state->count++;
		}
	}

	void test_CanDisposeAPromiseAfterResolved_Resolve(void* _state) {
		struct test_CanDisposeAPromiseAfterResolved_State* state = (struct test_CanDisposeAPromiseAfterResolved_State*)_state;
		(*state->resolveCalled) = true;
		return;
	}

	void test_CanDisposeAPromiseAfterResolved_Reject(void* _state) {
		struct test_CanDisposeAPromiseAfterResolved_State* state = (struct test_CanDisposeAPromiseAfterResolved_State*)_state;
		(*state->rejectCalled) = true;
		return;
	}

	void test_CanDisposeAPromiseAfterResolved_Dispose(void* _state) {
		struct test_CanDisposeAPromiseAfterResolved_State* state = (struct test_CanDisposeAPromiseAfterResolved_State*)_state;
		(*state->disposeCalled) = true;
		free(state);
		return;
	}

	void test_CanDisposeAPromiseAfterResolved() {
		bool resolveCalled = false;
		bool rejectCalled = false;
		bool disposeCalled = false;
		PromiseManager* promiseManager = PromiseManager_New();
		struct test_CanDisposeAPromiseAfterResolved_State* state = (struct test_CanDisposeAPromiseAfterResolved_State*)malloc(sizeof(test_CanDisposeAPromiseAfterResolved_State));
		state->count = 0;
		state->resolveCalled = &resolveCalled;
		state->rejectCalled = &rejectCalled;
		state->disposeCalled = &disposeCalled;

		promiseManager->AddPromise(promiseManager, (void*)state, test_CanDisposeAPromiseAfterResolved_Process, test_CanDisposeAPromiseAfterResolved_Resolve, test_CanDisposeAPromiseAfterResolved_Reject, test_CanDisposeAPromiseAfterResolved_Dispose);
		while (promiseManager->Count > 0) {
			promiseManager->Process(promiseManager);
		}
		if (resolveCalled && disposeCalled) {
			printf("[PASS] test_CanDisposeAPromiseAfterResolved\r\n");
		}
		else {
			printf("[FAIL] test_CanDisposeAPromiseAfterResolved\r\n");
		}
		promiseManager->Dispose(promiseManager);
	}
	//</test_CanDisposeAPromiseAfterResolved>
	///////////////////////////////////////////////


#ifdef __cplusplus
}
#endif