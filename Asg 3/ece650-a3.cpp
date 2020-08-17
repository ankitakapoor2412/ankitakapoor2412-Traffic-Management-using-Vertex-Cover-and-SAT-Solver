// BY ANKITA KAPOOR
// Student ID : 20811694
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <vector>

int main (int argc, char **argv) {
    int rgenToPython[2];
    int pythonToC[2];
    pipe(rgenToPython);
    pipe(pythonToC);
    std::vector<pid_t> childr;
    pid_t ch=fork();
    if(ch==0)
    {
        if(dup2(rgenToPython[1], STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error: while opening rgen"<<std::endl;
        }
        close(rgenToPython[0]);
        close(rgenToPython[1]);
        close(pythonToC[0]);
        close(pythonToC[1]);
        std::cerr<<execvp("./rgen",argv)<< "from execvp in rgen"<<std::endl;
        std::cerr << "Error: in rgen\n";
        abort ();
    }
    else if (ch < 0)
    {
        std::cerr << "Error: It cannot fork for first time.\n";
    }
    childr.push_back(ch);

    ch=fork();
    if(ch==0)
    {
        if(dup2(rgenToPython[0], STDIN_FILENO)!=0 || dup2(pythonToC[1],STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error: opening for python"<<std::endl;
        }
        close(rgenToPython[1]);
        close(rgenToPython[0]);
        close(pythonToC[0]);
        close(pythonToC[1]);
        execl("/usr/bin/python", "/usr/bin/python", "./ece650-a1.py", (char *)NULL);
        std::cerr << "Error: in python \n";
        abort ();
    }
    else if (ch < 0)
    {
        std::cerr << "Error: It cannot fork for second time.\n";
    }
    childr.push_back(ch);

    ch=fork();
    if(ch==0)
    {
        if(dup2(pythonToC[0], STDIN_FILENO)!=0)
        {
           std::cerr<<"Error: While opening assign2"<<std::endl;
        }
        close(pythonToC[1]);
        close(pythonToC[0]);
        close(rgenToPython[1]);
        close(rgenToPython[0]);
        execvp("./ece650-a2",argv);
    }
    else if (ch < 0)
    {
        std::cerr << "Error: could not fork for third time.\n";
    }
    childr.push_back(ch);

    if(dup2(pythonToC[1],STDOUT_FILENO)!=1)
    {
        std::cerr<<"Error: while opening console"<<std::endl;
    }
    close(rgenToPython[1]);
    close(rgenToPython[0]);
    close(pythonToC[0]);
    close(pythonToC[1]);
    while (!std::cin.eof())
    {
        std::string l;
        std::getline(std::cin, l);
        if (l == ""){
			break;
        }
        std::cout<<l<<std::endl;
    }
    
    for (pid_t kid : childr)
    {
        int stat;
        kill (kid, SIGKILL);
        waitpid(kid, &stat, 0);
    }
    return 0;
}
