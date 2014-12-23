// Following data structures used for additional testing.

typedef struct {
  char  brand[32];
  char  colour[32];
  float price;
} ShoeType;

typedef struct {
  char  material[32];
  float width;
  float length;
  float	height;	
  int   numberOfLegs;
} TableType;

typedef struct {
	char name[32];
	char recipesInvolvedIn[99][32];
  int  calories;
} FoodType;

typedef struct {
  char country[32];
  char name[32];
  int  population;
} CityType;