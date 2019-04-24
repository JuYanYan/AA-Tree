/*
 * AA Tree
 * Header: AA Tree and timer.
 * 2019-04-24
    MIT License

    Copyright (c) 2019 JuYan

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
class CStopWatch                                        // Timer on Windows. It is not important.
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

typedef int    treeData;
typedef struct _AATreeNode
{
    treeData        data;
    int             key;
    int             level;
    _AATreeNode    *left;
    _AATreeNode    *right;
}AATreeNode, *AATree;
