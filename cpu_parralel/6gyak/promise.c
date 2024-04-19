#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Promise
{
    int result;
    bool resolved;
} Promise;

void init_promise(Promise *promise);
void resolve_promise(Promise *promise, int result);
bool is_resolved(Promise *promise);
int get_result(Promise *promise);

void init_promise(Promise *promise)
{
    promise->resolved = false;
}

void resolve_promise(Promise *promise, int result)
{
    promise->result = result;
    promise->resolved = true;
}

bool is_resolved(Promise *promise)
{
    return promise->resolved;
}

int get_result(Promise *promise)
{
    return promise->result;
}

int main()
{
    Promise promise;
    init_promise(&promise);
    int result = compute_result();
    resolve_promise(&promise, result);
    int result2 = get_result(&promise);

    return 0;
}
