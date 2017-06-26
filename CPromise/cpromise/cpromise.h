#pragma once
#ifndef _CPROMISE_H
#define _CPROMISE_H

#include <stdlib.h>
#include "bsdqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum PromiseState {
	PENDING,
	RESOLVED,
	REJECTED
} PromiseState;


typedef struct PromiseEntry {
	void* state;
	PromiseState (*PendingHandler)(void* state);
	void(*ResolveHandler)(void* state);
	void(*RejectHandler)(void* state);
	void(*DisposeHandler)(void* state);

	LIST_ENTRY(PromiseEntry) entries;
} PromiseEntry;

typedef struct _PromiseManager PromiseManager;
struct _PromiseManager {
	//private:
	LIST_HEAD(promise_list_head, PromiseEntry) Promises;

	//public:
	int Count;
	void(*Process)(struct _PromiseManager*);
	void(*AddPromise)(struct _PromiseManager* self, void* state, PromiseState(*PendingHandler)(void* state), void(*ResolveHandler)(void* state), void(*RejectHandler)(void* state), void(*DisposeHandler)(void* state));
	void(*Dispose)(struct _PromiseManager*);
};

void PromiseManager_Dispose(struct _PromiseManager* self);
void PromiseManager_AddPromise(struct _PromiseManager* self, void* state, PromiseState(*PendingHandler)(void* state), void(*ResolveHandler)(void* state), void(*RejectHandler)(void* state), void(*DisposeHandler)(void* state));
void PromiseManager_Process(struct _PromiseManager* self);
struct _PromiseManager* PromiseManager_New(void);

#ifdef __cplusplus
}
#endif

#endif