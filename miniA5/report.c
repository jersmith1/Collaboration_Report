#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

/*
************************COMMENTS***********************************************************************
**PURPOSE**********************************************************************************************
*******************************************************************************************************
** AUTHOR ********* DEPARTMENT *********** DATE ***************** CHANGES *****************************
** Jeremy Smith *** Computer Science ***** November 11, 2020 **** Created code file and comments section
***************************************************************** Began writing pseudo and copied in the
***************************************************************** structure given in the assignment instructions
*******************************************************************************************************
****************************************** November 13, 2020 *** what am i returning? write majority of remaining code
*******************************************************************************************************
****************************************** November 14, 2020 ***  figure out how to write find collabs
***************************************************************** fix a lot of bugs tomorrow in main too many loops
*******************************************************************************************************
****************************************** November 15, 2020 *** some work on main and redid readLog
*******************************************************************************************************
****************************************** November 16, 2020 *** ensure printing to file_out works
*******************************************************************************************************
****************************************** November 17, 2020 *** fix compilation issues / debugging + bool typedef
***************************************************************** fix segmentation fault11 and minitester
*******************************************************************************************************
*/

typedef int boolean;
int t = 1;
int f =0;

struct logrecord
{
    char name[100];
    char IPAddress[50];
};

struct logrecord readLog(char* logline) 
{    
    char* token = strtok(logline, ",");
    char* data[7];
    int counter = 0;
    while (token != NULL)
    {
        data[counter] = token;
        token = strtok(NULL, ",");
    }
    struct logrecord student = {.name = *data[0], .IPAddress = *data[6]};
    //student.name = &data[0];
    //student.IPAddress = &data[6];
    return student;
    //parse a char array that contains a line from log
    //return a structure that contains the fields of interest
}

bool checkNameExists(FILE* csvfile, char* name, char* ip)   //maybe change to int or figure out how bool works
{
    char line[199];
    //ignore header
    fgets(line, 199, csvfile);
    //printf("%s\n",name);
    //printf("%s", line);
    //read remaining
    bool flag = f;

    int p = 0;

    while(fgets(line, 199, csvfile) != NULL)
    {
        p++;
    }

    //printf("%d",p);

    struct logrecord student[p];

    for(int j=0; j<p; j++)
    {
        student[j]=readLog(line); //need a pointer to line??? how?
        if (strcmp(student[j].name, name)==0)
        {
            flag = t;
        }
    } 

    /*while(fgets(line, 199, csvfile) != NULL)
    {
        //printf("%s", line);
        char* found;
        found = strstr(name, line);
        if(found != NULL)
        {
            //update IPADDRESS
            flag = t;
        }
    }*/
    return flag;
    //return f;
    //read through file looking for name
    //if found store ip associated with name to var ip
    //return success
    //refresh how booleans work and are returned in C think with 1 and 0 but idk how type works
}

bool findCollaborators(char* sname, char* sip, FILE* csvfile, FILE* rptfile)
{
    char line[199];

    //ignore header
    fgets(line, 199, csvfile);

    //read remaining
    int i=0;
    int p=0;

    while(fgets(line, 199, csvfile) != NULL)
    {
        p++;
    }

    struct logrecord student[p];

    for(int j=0; j<p; j++)
    {
        student[j]=readLog(line); //need a pointer to line??? how?
    }

    bool flag = f;

    while(fgets(line, 199, csvfile) != NULL)
    {

        if (strcmp(sname, student[i].name) != 0 && strcmp(student[i].IPAddress, sip) == 0)
        {
            fputs(student[i].name, rptfile);
            fputc('\n', rptfile);
            //write to report file
            flag = t;
        }
        else
        {
            char* outp = strcat("No collaborators found for ", sname);
            fputs(outp, rptfile);
            fputc('\n', rptfile);
            //flag = f; gone bc as soon as 1 is true it should be true default f
        }
        i++;
    }
    return flag;
    //conditions...
        //name!=sname
        //sip == IPAddress
    //go through csv
    //look for collabortors of sname by looking for ip entries that match sip
    //if any collaborators are found write it to the output report file
}

int main(int argc, char* argv[])
{
    FILE *file_in;
    FILE *file_out;
    char line[199]; //199 or 200
    char* studentName = argv[2];

    //printf("164");

    if (argc > 4)
    {
        fprintf(stderr, "Usage ./report <%s> \"<%s>\" <%s>\n", argv[1], argv[2], argv[3]);
        return 1;
    }

    //printf("171");

    //open output file
    file_out = fopen(argv[3], "a");

    //printf("177");

    //Open input file
    file_in = fopen(argv[1], "r");

    //printf("182");

    if (file_in == NULL)
    {
        fprintf(stderr, "Error, unable to open csv file \'%s\' for reading.\n", argv[1]);
        return 1;
    }

    //printf("190");

    if (checkNameExists(file_in, argv[2], "")==f)
    {
        fprintf(stderr, "Error, unable to locate %s\n", argv[2]);
        return 1;
    }

    //printf("198");

    if(file_out == NULL)
    {
        fprintf(stderr, "Error, unable to open the output file \'%s\'\n", argv[3]);
        return 1;
    }

    //ignore header
    fgets(line, 199, file_in);

    //printf("209");

    //get number of students
    int i=0;

    while(fgets(line, 199, file_in) != NULL)
    {
        i++;
    }

    //printf("219");

    struct logrecord student[i];

    //printf("223");

    //read remaining

    for(int j=0; j<i; j++)
    {
        student[j]=readLog(line);
        findCollaborators(student[j].name, student[j].IPAddress, file_in, file_out);
    }

    //printf("233");

    //close the file
    fclose(file_in);
    fclose(file_out);

    return 0;
}
