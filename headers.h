#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "bg_exit.h"
#include "prompt.h"
#include "pwd.h"
#include "ls.h"
#include "cd.h"
#include "pinfo.h"
#include "echo.h"
#include "insert.h"
#include "hist.h"
#include "display_history.h"
#include "jobs.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "ctrlc.h"
#include "ctrlz.h"

struct bg *first;
char home[1000];
char prev_dir[1000];
char temp_dir[1000];
char hist_string[1000];
char copy_string[1000];
int job_num;
int fg_pid;
char name[1000];
