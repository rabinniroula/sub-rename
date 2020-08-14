#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int EndsWith(const char *str, const char *suffix){
  if (!str || !suffix)
      return 0;
  size_t lenstr = strlen(str);
  size_t lensuffix = strlen(suffix);
  if (lensuffix >  lenstr)
      return 0;
  return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

char *strRemove(char *str, const char *sub) {
    char *p, *q, *r;
    if ((q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}

int main(void) {
  char vidFiles[50][100], srtFiles[50][100];
  int vc = 0, sc = 0, j = 0;
  DIR *dr;
  struct dirent *en;

  char ve[5], se[5];
  printf("Extension of video file : ");
  gets(ve);

  printf("Extension of subtitle file: ");
  gets(se);

  dr = opendir("."); //open all or present directory
  if (dr) {
    while ((en = readdir(dr)) != NULL) {
      if (EndsWith(en->d_name, ve)){
        strcpy(vidFiles[vc], en->d_name);
        vc++;
      }
      else if (EndsWith(en->d_name, se)){
        strcpy(srtFiles[sc], en->d_name);
        sc++;
      }
    }
    closedir(dr); //close all directory
  }

  if (sc != vc){
    printf("Number of vids and subtitles mismatch!\n");
    exit(0);
  }
  else{
    for(j = 0; j < vc; j++){
      printf("Changing %s to %s\n", srtFiles[j], strcat(strRemove(vidFiles[j], ve), se));
      if (rename(srtFiles[j], vidFiles[j]) == 0){
        printf("Files renamed successfully.\n");
      }
      else{
        fprintf(stderr, "Error renaming\n");
      }
    }
  }
  return(0);
}
