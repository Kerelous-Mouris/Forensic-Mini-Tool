#include<iostream>
#include </usr/include/x86_64-linux-gnu/sys/stat.h>
#include <stdio.h>
using namespace std;
int main()
{
	char fname[255];
	std::cout << "Enter absolute path for your file : ";                 //eg: /home/student/g1q4.cpp
	std::cin >> fname;
	struct stat var;                             //a variable that can store the stat information if the file we provide.
	int ret = stat(fname, &var);                        //call the fuction stat for file name ‘fname’ and store the values in ‘var’.

	if (ret < 0)
	{
		std::cout << "System call ‘stat’ exited with an error code " << ret << std::endl;
	}
	else
	{
		std::cout << "Device id : " << var.st_dev << std::endl;
		std::cout << "Inode number : " << var.st_ino << std::endl;
		std::cout << "Mode: " << var.st_mode << std::endl;
		std::cout << "UID: " << var.st_uid << std::endl;
		std::cout << "GID: " << var.st_gid << std::endl;
		std::cout << "Size: " << var.st_size << std::endl;
	}

	//you can get this structure by $man fstat (trick, not to be used in exams)
	struct stat
	{
		dev_t     st_dev;     /* ID of device containing file */
		ino_t     st_ino;     /* inode number */
		off_t     st_size;    /* total size, in bytes */
		unsigned short    st_mode;    /* protection */
		short   st_nlink;   /* number of hard links */
		short     st_uid;     /* user ID of owner */
		short     st_gid;     /* group ID of owner */
	};

}
