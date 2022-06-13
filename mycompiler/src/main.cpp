#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string>
extern char *optarg;
extern void codeToIR(char *input_file_path, char *output_file_path,int type,std::string function);

int main(int argc, char *argv[]){
    int arg_temp = 0;
    int type = 0;
    char *input_file_path = nullptr;
    char *output_file_path = nullptr;
    std::string fucntion;
    //-S <inputfile> -o <outputfile>
    if(argc == 5) {
        switch (argv[1][1])
        {
        case 's':
            type = 2;
            break;
        case 'i':
            type = 3;
            break;
        case 'a':
            type = 1;
            break;
        default:
            break;
        }
        output_file_path = argv[3];
        input_file_path = argv[4];
    }
    else if(argc==6) {
        output_file_path = argv[4];
        input_file_path = argv[5];
        fucntion = argv[2];
        type = 4;
    }
    codeToIR(input_file_path,output_file_path,type,fucntion);
    return 0;
}
