#include "cpromise.h"

#ifdef __cplusplus
extern "C" {
#endif

	struct _PromiseManager* PromiseManager_New() {
		struct _PromiseManager* self = (struct _PromiseManager*)malloc(sizeof(struct _PromiseManager));
		LIST_INIT(&self->Promises);
		self->Count = 0;
		self->Process = PromiseManager_Process;
		self->AddPromise = PromiseManager_AddPromise;
		self->Dispose = PromiseManager_Dispose;
		return self;
	}


	void PromiseManager_Process(struct _PromiseManager* self) {
		struct PromiseEntry *it, *it_tmp;
		LIST_FOREACH_SAFE(it, &self->Promises, entries, it_tmp)
		{
			if (it->PendingHandler > NULL) {
				PromiseState status = it->PendingHandler(it->state);

				if (status == RESOLVED) {
					if (it->ResolveHandler > NULL) {
						it->ResolveHandler(it->state);
					}
					if (it->DisposeHandler > NULL) {
						it->DisposeHandler(it->state);
					}
					LIST_REMOVE(it, entries);
					self->Count--;
					free(it);
				}
				else if (status == REJECTED) {
					if (it->RejectHandler > NULL) {
						it->RejectHandler(it->state);
					}
					if (it->DisposeHandler > NULL) {
						it->DisposeHandler(it->state);
					}
					LIST_REMOVE(it, entries);
					self->Count--;
					free(it);
				}
				else {
					//Still pending. (not yet resolved or rejected)
				}
			}
		}
	}

	void PromiseManager_AddPromise(struct _PromiseManager* self, void* state, PromiseState(*PendingHandler)(void* state), void(*ResolveHandler)(void* state), void(*RejectHandler)(void* state), void(*DisposeHandler)(void* state))
	{
		struct PromiseEntry* item = (PromiseEntry*)malloc(sizeof(PromiseEntry));
		item->PendingHandler = PendingHandler;
		item->RejectHandler = RejectHandler;
		item->ResolveHandler = ResolveHandler;
		item->DisposeHandler = DisposeHandler;
		item->state = state;
		LIST_INSERT_HEAD(&self->Promises, item, entries);
		self->Count++;
	}

	void PromiseManager_Dispose(struct _PromiseManager* self) {
		struct PromiseEntry *it, *it_tmp;
		LIST_FOREACH_SAFE(it, &self->Promises, entries, it_tmp)
		{
			if (it->DisposeHandler != NULL) {
				it->DisposeHandler(it->state);
			}
			LIST_REMOVE(it, entries);
			self->Count--;
			free(it);
		}
		free(self);
	}
#ifdef __cplusplus
}
#endif