# Week 2
### **Đề bài: STRING AND SCANDIR**
scandir
[scandir(3) - Linux manual page (man7.org)](https://man7.org/linux/man-pages/man3/scandir.3.html)
[Directory Entries (The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html)
string allocation: [Ex3.c](./exc3.c)

- Viết 1 chương trình (myscan) nhận tham số từ dòng lệnh sau đó in ra file `myscan.html` ở cùng thư mục thực thi nội dung các file và thư mục con của đường dẫn truyền vào tham số chương trình.
- Nội dung ở dạng html, mỗi file/thư mục trên một dòng, tên file viết nghiêng, tên thư mục in đậm
Ví dụ khi thực thi chương trình: `./myscan /mnt/c/Temp`
Thì chương trình sẽ in ra file `./myscan.html` nội dung của thư mục `/mnt/c/Temp`

### Các hàm cần chú ý
#### - scandir(): scan a directory for matching entries
- Hàm này nằm trong libc luôn
- The scandir() function returns the number of directory entriesselected.  On error, -1 is returned, with errno set to indicatethe error.
- The alphasort() and versionsort() functions return an integer less than, equal to, or greater than zero if the first argument is considered to be respectively less than, equal to, or greater than the second.
- Example:
```c
#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--) {
        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}
```
Trong ví dụ trên, struct dirrent gồm các thành phần sau:
```cstruct dirent {
    ino_t          d_ino;       /* inode number */
    off_t          d_off;       /* offset to the next dirent */
    unsigned short d_reclen;    /* length of this record */
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types */
    char           d_name[256]; /* filename */
};
```
Hàm scandir nhận vào các tham số:
```
int scandir(const char *restrict dirp,
                   struct dirent ***restrict namelist,
                   int (*filter)(const struct dirent *),
                   int (*compar)(const struct dirent **,
                                 const struct dirent **));
```
Ví dụ về `filter` được đặt tại [đây](./test.c)
### Source code
Cuối cùng là lời giải của bài tập: [Source code](./myscan.c)
Lời giải của thầy Vinh: [Source code](./thayVinhscan.c)