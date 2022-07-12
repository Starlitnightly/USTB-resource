/*
 * ConfigManager.h
 *
 *  Created on: 2018年7月28日
 *      Author: oftenlin
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_
#define SIZE_FILENAME 50


class ConfigManager {
public:
	ConfigManager(const char *filename) { ConfigFileLoad(filename); };
	~ConfigManager() { ConfigFileFree(); };
	//加载ini文件至内存

	char gFilename[SIZE_FILENAME];
	char *gBuffer;
	int gBuflen;
	int ConfigFileLoad(const char *filename);
	//释放ini文件所占资源
	void ConfigFileFree();
	int FindSection(const char *section, char **sect1, char **sect2, char **cont1, char **cont2, char **nextsect);
	//获取字符串，不带引号
	int GetString(const char *section, const char *key, char *value, int size, const char *defvalue);
	//获取整数值
	int GetInt(const char *section, const char *key, int defvalue);
	//获取浮点数
	double GetDouble(const char *section, const char *key, double defvalue);
	int GetValue(const char *section, const char *key, char *value, int maxlen, const char *defvalue);
	//设置字符串：若value为NULL，则删除该key所在行，包括注释
	int SetString(const char *section, const char *key, const char *value);
	//设置整数值：base取值10、16、8，分别表示10、16、8进制，缺省为10进制
	int SetInt(const char *section, const char *key, int value, int base = 10);
	//    int iniGetIP(const char *section, const char *key, BasicHashTable *hashtable, int size, const char *defvalue);
};


#endif /* CONFIGMANAGER_H_ */