#ifndef _FILE_OPER_H_
#define _FILE_OPER_H_

//读取./data/目录下所有文件到内存
void get_all_files(void);

//将./data/目录下所有文件打包到./PackageData.bin/中
void package_files(void);

//将文件目录信息写入到./MetaData.bin中
void write_files_info(void);

//将文件目录信息从./MetaData.bin中读取出来
void read_files_info(void);

//将./PackageData.bin中的文件释放到./data/目录下
void unpack_files(void);

//删除./data/目录下所有文件
void delete_files(void);

#endif // !_FILE_OPER_H_
