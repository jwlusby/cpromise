// CPromise.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cpromise_tests/cpromise_tests.h"


int main()
{
	test_CanInitializeAndDisposePromiseManager();
	test_CanProcessWithEmptyList();
	test_CanAddAPromise();
	test_CanProcessAPromise();
	test_CanResolveAPromise();
	test_CanRejectAPromise();
	test_CanDisposeAPromiseAfterRejected();
	test_CanDisposeAPromiseAfterResolved();

	while (true);
	return 0;
}

