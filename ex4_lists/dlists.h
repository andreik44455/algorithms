union data {
   char* programme_name;
   char* room_number;
};

enum work{stuff, student, neither};

typedef struct person {
  char* name;
  int age;
  struct person *pNext;
  struct person  *pPrevious;
  enum work staff_or_student;
  union data extraInfo;
} person;








person* insert_start(person* people, char *name, int age, char *info, int person_type);
person* insert_end(person* people, char *name, int age, char *info, int person_type);
person* insert_sorted(person* people, char *name, int age,int compare_people(person* old, person* new), char *info, int person_type);
