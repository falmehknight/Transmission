//
// Created by flame on 23-3-10.
//

#include <iostream>
#include <string>
#include "ClientOp.h"
using namespace std;

int usage();
int main()
{
    // 创建客户端操作类对象
    ClientOp op("config.json");
    while (1)
    {
        int sel = usage();
        switch (sel)
        {
            case 1:
                // 秘钥协商
                op.secKeyAgree();
                break;
            case 2:
                op.secKeyCheck();
                // 秘钥校验
                break;
            case 3:
                // 秘钥注销
                op.secKeyLogout();
            default:
                break;

        }
    }
    cout << "客户端退出, bye,bye..." << endl;
    return 0;
}

int usage()
{
    int nSel = -1;
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n  /*     1.密钥协商                                            */");
    printf("\n  /*     2.密钥校验                                            */");
    printf("\n  /*     3.密钥注销                                            */");
    printf("\n  /*     4.密钥查看                                            */");
    printf("\n  /*     0.退出系统                                            */");
    printf("\n  /*************************************************************/");
    printf("\n  /*************************************************************/");
    printf("\n\n  选择:");

    scanf("%d", &nSel);
    while (getchar() != '\n');

    return nSel;
}
