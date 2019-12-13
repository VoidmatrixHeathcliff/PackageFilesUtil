#include <stdio.h>
#include <string.h>
#include <io.h>
#include <atlstr.h>  
#include <direct.h>

#define BUFFSIZE 4096
#define MAX_FNUM 50000

struct _finddata_t files_info[MAX_FNUM];
size_t file_num = 0;

char* direct_path;
char  src_file_path[200];
const char* src_files_path = "./data/*.*";
const char* data_file_name = "PackageData.bin";
const char* meta_data_name = "MetaData.bin";

void init_path(void)
{
	if ((direct_path = _getcwd(NULL, 0)) != NULL)
	{
		memcpy(src_file_path, direct_path, sizeof(src_file_path));
		CString cstr;
		cstr.Format(src_file_path);
		cstr.Replace("\\", "\\\\");
		strcpy(src_file_path, cstr);
	}
}

void get_all_files(void)
{
	init_path();
	struct _finddata_t file;
	intptr_t HANDLE = _findfirst(src_files_path, &file);
	size_t temp_num = 0;
	do
	{
		if (temp_num <= 2)
		{
			file_num = 0;
		}
		files_info[file_num] = file;
		file_num++;
		temp_num++;
	} while (_findnext(HANDLE, &file) == 0);

	_findclose(HANDLE);
}

void package_files(void)
{
	FILE* source;
	FILE* dest;
	size_t bytes;
	static char temp[4096];

	if ((dest = fopen(data_file_name, "wb+")) == NULL)
	{
		printf("Can't open data file : PackageData.bin !\n");
		return;
	}

	for (size_t i = 0; i < file_num; i++)
	{
		char temp_path[200];
		memcpy(temp_path, src_file_path, sizeof(src_file_path));
		strcat(temp_path, "\\\\data\\\\");
		char* path = strcat(temp_path, files_info[i].name);
		if ((source = fopen(path, "rb")) == NULL)
		{
			printf("Can't open source file : %s !\n", files_info[i].name);
		}
		else
		{
			while ((bytes = fread(temp, sizeof(char), BUFFSIZE, source)) > 0)
			{
				fwrite(temp, sizeof(char), bytes, dest);
			}
			printf("File %s\tpackaged SUCCESS !\n", files_info[i].name);
			fclose(source);
		}		
	}		
	fclose(dest);
}

void write_files_info(void)
{
	FILE* dest;
	if ((dest = fopen(meta_data_name, "wb+")) == NULL)
	{
		printf("Can't open meta file : MetaData.bin !\n");
		return;
	}
	fwrite(files_info, MAX_FNUM, sizeof(struct _finddata_t), dest);
	fclose(dest);
}

void read_files_info(void)
{
	FILE* source;
	if ((source = fopen(meta_data_name, "rb+")) == NULL)
	{
		printf("Can't open meta file : MetaData.bin !\n");
		return;
	}
	fread(files_info, MAX_FNUM, sizeof(struct _finddata_t), source);
	fclose(source);
}

void unpack_files(void)
{
	init_path();

	FILE* source;
	FILE* dest;
	if ((source = fopen(data_file_name, "rb+")) == NULL)
	{
		printf("Can't open data file : PackageData.bin !\n");
		return;
	}

	size_t index = 0;
	while (strlen(files_info[index].name) != 0)
	{
		char temp_path[200];
		memcpy(temp_path, src_file_path, sizeof(src_file_path));
		strcat(temp_path, "\\\\data\\\\");
		char* path = strcat(temp_path, files_info[index].name);

		printf("%s\n", path);
		if ((dest = fopen(path, "wb+")) == NULL)
		{
			printf("Can't open dest file : %s\t!\n", files_info[index].name);
			index++;
			continue;
		}

		char* buffer = (char*)malloc(files_info[index].size);
		fread(buffer, sizeof(char), files_info[index].size / sizeof(char), source);
		fwrite(buffer, sizeof(char), files_info[index].size / sizeof(char), dest);
		fclose(dest);
		free(buffer);
		index++;
	}
	fclose(source);
}

void delete_files(void)
{
	if ((direct_path = _getcwd(NULL, 0)) != NULL)
	{
		memcpy(src_file_path, direct_path, sizeof(src_file_path));
		CString cstr;
		cstr.Format(src_file_path);
		cstr.Replace("\\", "\\\\");
		strcpy(src_file_path, cstr);
	}
	init_path();
	char* current_path = _getcwd(NULL, 0);
	char command[200] = "del \"";
	if (current_path == NULL)
	{
		printf("Failed to get current directory !");
		return;
	}
	strcat(command, current_path);
	strcat(command, "\\data\\");
	strcat(command, "*.*\" /f/s/q/a");
	printf("%s\n", command);
	system(command);
}
