#include <stdio.h>
#include <dirent.h>
#include <cs50.h>
#include <string.h>

char * files;
string name, n_name;
DIR *dir;
struct dirent *folder;

int main(void)
{   

    printf("Here are all the folders in the root folder\n");
    dir = opendir(".");
    printf("-------------------------\n");
    while((folder=readdir(dir)) != NULL)
    {
        if ( strcmp((folder->d_name), ".") == 0|| strcmp((folder->d_name), "..") == 0){
            continue;
        } else{
            printf("%s\n", folder->d_name);
        }
    }
    printf("-------------------------\n");
    closedir(dir);

    while (true){

        name = get_string("Pick a file to rename: ");
        printf("Pick a new name for %s \n", name);
        n_name = get_string("New name: ");

        if (rename(name, n_name) == 0){
            printf("%s Successfully renamed to %s!\n", name, n_name);
            break;
        } else{
            continue;
        }
    }


}
