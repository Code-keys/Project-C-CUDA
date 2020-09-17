#pragma once

#include "cudakenel.cuh"

#include <iostream>
using namespace std;

#define DX 200


class CTest
{
public:
    int *a;
    int *b;
    int *c;

    void SetParameter();
    void AddNum();
    void Show();
    void Evolution();
};

void CTest::SetParameter()
{
    cudaMallocManaged(&a, sizeof(int) * DX);
    cudaMallocManaged(&b, sizeof(int) * DX);
    cudaMallocManaged(&c, sizeof(int) * DX);

    for (int f = 0; f<DX; f++)
    {
        a[f] = f;
        b[f] = f + 1;
    }

}

void CTest::AddNum()
{
    Interface(a, b, c, DX);
}

void CTest::Show()
{
    cout << " a     b    c"  << endl;

    for (int f = 0; f<DX; f++)
    {
        cout << a[f] << " + " << b[f] << "  = " << c[f] << endl;
    }
}

void CTest::Evolution()
{
    SetParameter();
    AddNum();
    Show();
}