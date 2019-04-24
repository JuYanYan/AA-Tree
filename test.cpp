/*
 |Test program.
*/
#include <iostream>
#include "AATree.h"
#include <math.h>
#include <Windows.h>
#define  _TIME_TEST_
class CStopWatch
{
public:
    CStopWatch();
    void start();
    void stop();
    double getElapsedTime();
private:
    LARGE_INTEGER m_start;
    LARGE_INTEGER m_stop;
    LARGE_INTEGER m_frequency;
};

CStopWatch::CStopWatch()
{
    m_start.QuadPart = 0;
    m_stop.QuadPart = 0;
    QueryPerformanceFrequency(&m_frequency);
}
// Start
void CStopWatch::start()
{
    QueryPerformanceCounter(&m_start);
}
// Stop
void CStopWatch::stop()
{
    QueryPerformanceCounter(&m_stop);
}
// Computing time(s)
double CStopWatch::getElapsedTime()
{
    double  r;
    LARGE_INTEGER time;
    time.QuadPart = m_stop.QuadPart - m_start.QuadPart;
    r = (double)time.QuadPart / (double)m_frequency.QuadPart;
    r *= 1000000;
    return r;
}

int myrand(int max)
{
    int v;
    v = rand() | (rand() << 16);
    v %= max;
    return v;
}

#ifdef _TIME_TEST_

void test_delete(AATree *aat, int key)
{
    CStopWatch t;
    t.start();
    aat_deleteData(aat, key);
    t.stop();
    printf("Delete: %d, Time:%lfus\n", key, t.getElapsedTime());
}

void test_search(AATree aat, int key)
{
    treeData   *d;
    CStopWatch  t;
    t.start();
    aat_searchData(aat, key, &d);
    t.stop();
    printf("  Find: %d, Time:%lfus, Result: ", key, t.getElapsedTime());
    if (d == NULL)
        printf("Not found.\n");
    else
        printf("%d\n", *d);
}

int main()
{
    AATree      aat = NULL;
    CStopWatch  t;
    int         k, i, n, dat;
    printf("Insert(10^8): ");
    std::cin >> n;
    n *= 100000000;
    t.start();
    for (i = 0; i < n; i++)
    {
        k = i;
        dat = k ^ myrand(n);
        aat_insertData(&aat, k, &dat);
    }
    t.stop();
    printf("Insert: %d, Time: %lfs\n", n, t.getElapsedTime() / 1000000);
    test_delete(&aat, myrand(n));
    test_delete(&aat, myrand(n));
    test_delete(&aat, myrand(n));
    test_delete(&aat, myrand(n));
    test_search(aat, myrand(n));
    test_search(aat, myrand(n));
    test_search(aat, myrand(n));
    test_search(aat, myrand(n));
    system("pause");
    aat_deleteTree(&aat);
    system("pause");
    return 0;
}
#else
int main()
{
    AATree      aat = NULL;
    int         k, i, n, dat;
    printf("Insert: ");
    std::cin >> n;
    for (i = 0; i < n; i++)
    {
        k = i;
        dat = k ^ myrand(n);
        aat_insertData(&aat, k, &dat);
    }
    aat_printTree(stdout, aat, 0);
    aat_deleteTree(&aat);
    system("pause");
    return 0;
}
#endif
