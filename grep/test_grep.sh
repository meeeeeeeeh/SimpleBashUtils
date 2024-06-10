#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test_file.txt"
echo "" > log.txt

for var in -e -i -v -c -l -n -h -s
do
    for var2 in 'with' 'Papers' 'text' 'as'
    do
        TEST1="$var $var2 $TEST_FILE"
        echo "$TEST1"
        ./s21_grep $TEST1 > s21_grep.txt
        grep $TEST1 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
            (( COUNTER_SUCCESS++ ))
            echo " \033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
        else
            echo "$TEST1" >> log.txt
            (( COUNTER_FAIL++ ))
            echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
        fi
        rm s21_grep.txt grep.txt log.txt
    done
done

for var in -e
do
    for var2 in 'with' 'Papers' 'text' 'as'
    do
        for var3 in -i -v -c -l -n -h -s -iv -in -ic -il -is -vc -vl -vn -vh -vs
        do
            TEST1="$var $var2 $var3 $TEST_FILE"
            echo "$TEST1"
            ./s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                (( COUNTER_SUCCESS++ ))
                echo "\033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
            else
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
                echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
            fi
            rm s21_grep.txt grep.txt log.txt
        done
    done
done

for var in -e
do
    for var2 in 'with' 'Papers' 'text' 'as'
    do
        for var3 in -i -v -c -l -n -h -s -vc -vl -vn -vh -vs
        do
            for var4 in -e
            do
                for var5 in 'as' 'cited' 'so' 'the'
                do
                    TEST1="$var $var2 $var3 $var4 $var5 $TEST_FILE"
                    echo "$TEST1"
                    ./s21_grep $TEST1 > s21_grep.txt
                    grep $TEST1 > grep.txt
                    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                    then
                        (( COUNTER_SUCCESS++ ))
                        echo "\033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
                    else
                        echo "$TEST1" >> log.txt
                        (( COUNTER_FAIL++ ))
                        echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
                    fi
                    rm s21_grep.txt grep.txt log.txt
                done
            done
        done
    done
done

for var in -e
do
    for var2 in 'with' 'Papers' 'text'
    do
        for var3 in -e
        do
            for var4 in 'as' 'cited'
            do
                for var5 in -e
                do
                    for var6 in 'so' 'the'
                    do
                        TEST1="$var $var2 $var3 $var4 $var5 $var6 $TEST_FILE"
                        echo "$TEST1"
                        ./s21_grep $TEST1 > s21_grep.txt
                        grep $TEST1 > grep.txt
                        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                        then
                            (( COUNTER_SUCCESS++ ))
                            echo "\033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
                        else
                            echo "$TEST1" >> log.txt
                            (( COUNTER_FAIL++ ))
                            echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
                        fi
                        rm s21_grep.txt grep.txt log.txt
                        
                    done
                done
            done
        done
    done
done

for var in -e
do
    for var2 in 'with' 'Papers' 'text'
    do
        for var3 in -e
        do
            for var4 in 'He' 'it' 'Thompson'
            do
                for var5 in -e
                do
                    for var6 in 'so' 'the'
                    do
                        for var7 in -v -c -l -n -h -s -vl -vn -vh -vs
                        do
                            TEST1="$var $var2 $var3 $var4 $var5 $var6 $var7 $TEST_FILE"
                            echo "$TEST1"
                            ./s21_grep $TEST1 > s21_grep.txt
                            grep $TEST1 > grep.txt
                            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                            then
                                (( COUNTER_SUCCESS++ ))
                                echo "\033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
                            else
                                echo "$TEST1" >> log.txt
                                (( COUNTER_FAIL++ ))
                                echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
                            fi
                            rm s21_grep.txt grep.txt log.txt
                        done
                    done
                done
            done
        done
    done
done

echo "\033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
echo "\033[31mFAIL: $COUNTER_FAIL\033[0m"
