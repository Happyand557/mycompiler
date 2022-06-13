#!/bin/bash

APPFIX=""
WINOS=0

# OS类别
OSKind=`uname -s`
    
# 机器位数
OS3264=`uname -m`

# 单个测试用例测试
function dotestcase() 
{
    CFILELIST=`ls $1*.c`

    # 要查找的C文件名
    CFILE=""

    n=0
    for cfilename in $CFILELIST
    do
        CFILE=$cfilename
        n=`expr $n + 1`
    done

    if [ $n -ne 1 ]; then
        return
    fi

    # 去掉C文件后缀，保留文件名
    TESTNAME=${CFILE%%.*}

    INFILE="${TESTNAME}.in"
    OUTFILE="${TESTNAME}.out"
    RESULTFILE="${TESTNAME}.result"
    IRFILE="${TESTNAME}.ir"

    CMDNAME="../IRCompiler/${OSKind}-${OS3264}/IRCompiler${APPFIX} -S -I -o ${IRFILE} ${CFILE}"

    OUTSTR=`eval ${CMDNAME} 2>&1`
    RUNRESULT=$?

    if [ $RUNRESULT -ne 0 ]; then
        echo "${CFILE} NG"
    else
        echo "${CFILE} OK"
    fi
}

TestCaseNum_From=0
TestCaseNum_To=102

if [ $# -eq 1 ]; then
    TestCaseNum_From=$1
    TestCaseNum_To=$1
fi

if [ $# -ge 2 ]; then
    TestCaseNum_From=$1
    TestCaseNum_To=$2
fi

PlatformOS=`uname -a`

if [[ ${PlatformOS} =~ "MINGW" ]];then
    APPFIX=".exe"
    WINOS=1
    OSKind="MINGW"
fi

for ((i = $TestCaseNum_From; i <= $TestCaseNum_To; i ++))
do
    TestCaseNo=`printf '%03d' $i`
    dotestcase $TestCaseNo
done
