/*
 * ��װ���ߺ���
 *
 *  Created on: 2015��10��10��
 *      Author: skywalker
 */

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

//�ַ����ָ��
vector<string> split(string str, string pattern);

/**
 * stringתfloat
 */
float string2Float(string str);

/**
 * floatתstring
 */
string float2String(float num);

/**
 * ������д�뵽ָ�����ļ�
 * @param path �ļ�Ŀ¼
 * @param data ��Ҫд�������
 */
void write2File(string path, string data);

/**
 * ���ļ���ȡ����
 * @return ���ж�ȡ�Ľ��
 */
vector<string> readFile(string path);

#endif
