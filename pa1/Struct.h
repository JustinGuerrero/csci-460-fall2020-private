// type def photo struct for pa1
// justin guerrero


typedef struct{
	char photo[10];
}photoStruct;


int resizePhoto(photoStruct photo[], int arrLength);
void thumbNail(photoStruct photo[], int arrLength);
void askUserRotate(photoStruct photo[], int arrLength);
char askForCaption(photoStruct photo[]);
void orientatePhoto(photoStruct photo[], int arrLength);