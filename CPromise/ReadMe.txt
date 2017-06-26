========================================================================
    CPromise: A C library for basic promise-like deferred execution
========================================================================

The PromiseManager structure handles processing and calling of the promise delegates. This is done by keeping
a list of simple state machines with delegates that handle the processing and updating. Every promise should 
have four delegates
-PendingHandler: Called on every 'Process()' until it returns either a Resolved or Rejected status.
-ResolveHandler: Called after PendingHandler returns a Resolved status
-RejectHandler: Called after PendingHandler returns a Rejected status
-DisposeHandler: Called after the ResolveHandler or RejectHandler has completed to free the state resources


PromiseManager* PromiseManager_New()
Creates and returns a pointer to a new PromiseManager

PromiseManager Properties:
int Count: Stores the current count of unfulfilled promises

PromiseManager Methods:
	void AddPromise(struct _PromiseManager* self, void* state, PromiseState(*PendingHandler)(void* state), void(*ResolveHandler)(void* state), void(*RejectHandler)(void* state), void(*DisposeHandler)(void* state));
		self: Pointer to the instance of the PromiseManager that the promise should be added to
		state: Pointer to the state object that should be associated with the promise
		ResolveHandler: Function pointer to the function that will be called when (if) the promise resolves
		RejectHandler: Function pointer to the function that will be called when (if) the promise is rejected
		DisposeHandler: Function pointer to the function that will be called after the promise has been resolved/rejected to dispose of the state object and free up memory held by it.

	void Dispose(struct _PromiseManager* self)
		self: Pointer to the instance of the PromiseManager that the promise should be added to

	void Process(struct _PromiseManager* self, void* state)
		self: Pointer to the instance of the PromiseManager that the promise should be added to
		state: Pointer to the state object that should be associated with the promise