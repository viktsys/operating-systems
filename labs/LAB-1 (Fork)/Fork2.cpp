#include <iostream>
#include <string>

// Required by for routine
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>   // Declaration for exit()

using namespace std;

int x = 2;

int main()
{
   string id;
   int    Y  = 20;

   pid_t pID = fork();
   pID = fork();
   if (pID == 0)                // child
   {
      id  = "A";
      x++;
      Y++;
    }
    else                                   // parent
    {
      id = "B";
    }

    cout << id;
    cout << " X: " << x;
    cout << " Y: "  << Y << endl;
}
