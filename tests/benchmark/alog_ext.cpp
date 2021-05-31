#include <benchmark/benchmark.h>
#include "alog/logger.h"
#include "alog-extensions/adapters/qt_qml_adapter.h"

static void ALog_Ext_Basic(benchmark::State& state)
{
    int i = 0;

    while (state.KeepRunning())
        i++;

    (void)i;
}

BENCHMARK(ALog_Ext_Basic);

BENCHMARK_MAIN();
