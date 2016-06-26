/*
 * 封装工具函数
 *
 *  Created on: 2015年10月10日
 *      Author: skywalker
 */

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

//字符串分割函数
vector<string> split(string str, string pattern);

/**
 * string转float
 */
float string2Float(string str);

/**
 * float转string
 */
string float2String(float num);

/**
 * 将数据写入到指定的文件
 * @param path 文件目录
 * @param data 需要写入的数据
 */
void write2File(string path, string data);

/**
 * 从文件读取数据
 * @return 逐行读取的结果
 */
vector<string> readFile(string path);

#endif
