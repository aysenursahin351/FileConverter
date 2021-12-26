#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tag{
char name[5]; //utf16
 char surname[8]; //utf8 
 char gender[7]; 
 char email[6];
 char phone_number[13];
 char address[8];
 char level_of_education[19];
 char income_level[13]; // given little-endian
 char expenditure[12]; // given big-endian 
 char currency_unit[14];
 char currentMood[12];
 char height[7];
 char weight[7];  
};
 struct record {
 char name[64]; //utf16
 char surname[32]; //utf8 
 char gender; 
 char email[32];
 char phone_number[16];
 char address[32];
 char level_of_education[8];
 unsigned int income_level; // given little-endian
 unsigned int expenditure; // given big-endian 
 char currency_unit[16];
 char currentMood[32];
 float height;
 unsigned int weight;
};
u_int32_t forExpenditure(struct record input){
     u_int32_t expenditure = input.expenditure; // expenditure
    u_int32_t result = ((expenditure>>24)&0xff) |  ((expenditure<<8)&0xff0000) | ((expenditure>>8)&0xff00) | ((expenditure<<24)&0xff000000);
    return result;
 }
 u_int32_t forIncomeLevel(struct record input){
     u_int32_t income_level = input.income_level; // income level
    u_int32_t b1,b2,b3,b4; 
    u_int32_t result;

    b1 =(income_level & 0x000000ff) << 24u;
    b2 =(income_level & 0x0000ff00) << 8u;
    b3 =(income_level & 0x00ff0000) << 8u;
    b4 =(income_level & 0xff000000) << 24u;

    result =  b1 | b2 | b3|b4 ;
    return result;
 }
 
void create_XmlData(FILE *fxml,struct record input,int id,struct tag header)
{
   
fprintf (fxml,"     <row id=\"%d\">\n",id);
fprintf (fxml,"         <%s>%s</%s>\n",header.name,input.name,header.name);
fprintf (fxml,"         <%s>%s</%s>\n",header.surname,input.surname,header.surname);
fprintf (fxml,"         <%s>%c</%s>\n",header.gender,input.gender,header.gender);
fprintf (fxml,"         <%s>%s</%s>\n",header.email,input.email,header.email);
fprintf (fxml,"         <%s>%s</%s>\n",header.phone_number,input.phone_number,header.phone_number);
fprintf (fxml,"         <%s>%s</%s>\n",header.address,input.address,header.address);
fprintf (fxml,"         <%s>%s</%s>\n",header.level_of_education,input.level_of_education,header.level_of_education);
fprintf (fxml,"         <%s bigEnd=\"%u\">%u</%s>\n",header.income_level,forIncomeLevel(input),input.income_level,header.income_level);
fprintf (fxml,"         <%s bigEnd=\"%u\">%u</%s>\n",header.expenditure,input.expenditure,forExpenditure(input),header.expenditure);
fprintf (fxml,"         <%s>%s</%s>\n",header.currency_unit,input.currency_unit,header.currency_unit);
fprintf (fxml,"         <%s>%s</%s>\n",header.currentMood,input.currentMood,header.currentMood);
fprintf (fxml,"         <%s>%f</%s>\n",header.height ,input.height,header.height);
fprintf (fxml,"         <%s>%u</%s>\n",header.weight,input.weight,header.weight);
fprintf (fxml,"     </row>\n");
}

void Bin2XML(const char* inputfile,const char* outputfile){
    FILE *file_input;
    FILE *file_output=fopen(outputfile,"w");
    struct record input;
    struct tag header;
	file_input = fopen (inputfile, "r");
    if (file_input == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }   
    
int counter;int id=0;
fprintf ( file_output,"<records>\n");
for ( counter=1; counter <= 51; counter++){
    fread(&input, sizeof(struct record), 1, file_input);
    if(counter==1){// This is for tag structure
         strcpy(header.name ,input.name);
         strcpy(header.surname ,input.surname);
          if(strcmp(header.gender,"gender")!=0){
        strcpy(header.gender , "gender");
        }
         strcpy(header.email,input.email);
         strcpy(header.phone_number , input.phone_number);
         strcpy(header.address,input.address);
        if(strcmp(header.level_of_education,"level_of_education")!=0){
      strcpy(header.level_of_education,"level_of_education");
      }
      if(strcmp(header.income_level,"income_level")!=0){
      strcpy(header.income_level,"income_level");
     }
     if(strcmp(header.expenditure,"expenditure")!=0){
      strcpy(header.expenditure,"expenditure");
  }
        strcpy(header.currency_unit,input.currency_unit);
        strcpy(header.currentMood,input.currentMood);
        
  if(strcmp(header.height,"height")!=0){
      strcpy(header.height,"height");
  }
  if(strcmp(header.weight,"weight")!=0){
      strcpy(header.weight,"weight");
  }
        
    }
    if(counter>1){
     create_XmlData(file_output,input,id,header);	
    }     
 id++;
}
printf ( file_output,"</records>\n");
fclose (file_input);
fclose(file_output);
}
int main(int argc,char*argv[]) {
  Bin2XML(argv[1],argv[2]) ;

return 0;
}